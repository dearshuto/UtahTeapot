use crate::{Float2, Float3};

pub struct BezierSurface {
    _control_point_position: [Float3; 16],
    _control_point_normal: [Float3; 16],
    _positions: Vec<Float3>,
    _normals: Vec<Float3>,
    _indices: Vec<u32>,
}

impl BezierSurface {
    pub fn new() -> Self {
        Self {
            _control_point_position: [Float3 {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }; 16],
            _control_point_normal: [Float3 {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }; 16],
            _positions: Vec::new(),
            _normals: Vec::new(),
            _indices: Vec::new(),
        }
    }

    pub fn update(&mut self, div: u8, sub_div: u8) {
        self.update_control_point_normal();

        self._indices.clear();
        self._positions.clear();
        self._normals.clear();

        // 縦横の超点数
        // 両端に頂点があるので +2 してます
        let n_count = (div as u32) + 2;
        let m_count: u32 = (sub_div as u32) + 2;

        let mut uv = Vec::<Float2>::new();
        uv.resize((n_count * m_count) as usize, Float2::default());
        self._positions
            .resize((n_count * m_count) as usize, Float3::default());

        let stride_u = 1.0 / ((div as f32) + 1.0);
        let stride_v = 1.0 / ((sub_div as f32) + 1.0);

        for n in 0..n_count {
            for m in 0..m_count {
                uv[(n + n_count * m) as usize].x = stride_u * (n as f32);
                uv[(n + n_count * m) as usize].y = stride_v * (m as f32);
            }
        }

        for n in 0..n_count {
            for m in 0..m_count {
                let current_u = uv[(n + n_count * m) as usize].x;
                let current_v = uv[(n + n_count * m) as usize].y;

                // すべての頂点からの影響を足し込む
                for i in 0..4 {
                    for j in 0..4 {
                        let control_point = &self._control_point_position[i + j * 4];
                        let bernstein_polynormal_u =
                            Self::compute_bernstein_polynormal(current_u, i as u32);
                        let bernstein_polynormal_v =
                            Self::compute_bernstein_polynormal(current_v, j as u32);

                        let current_index = (n + m * n_count) as usize;
                        self._positions[current_index].x +=
                            bernstein_polynormal_u * bernstein_polynormal_v * control_point.x;
                        self._positions[current_index].y +=
                            bernstein_polynormal_u * bernstein_polynormal_v * control_point.y;
                        self._positions[current_index].z +=
                            bernstein_polynormal_u * bernstein_polynormal_v * control_point.z;
                    }
                }
            }
        }

        // ポリゴンとして登録
        for n in 0..(n_count - 1) {
            for m in 0..(m_count - 1) {
                let left_up = n + m * n_count;
                self._indices.push(left_up as u32);
                self._indices.push((left_up + 1) as u32);
                self._indices.push((left_up + n_count + 1) as u32);

                self._indices.push(left_up as u32);
                self._indices.push((left_up + n_count + 1) as u32);
                self._indices.push((left_up + n_count) as u32);
            }
        }
    }

    pub fn get_positions(&self) -> &[Float3] {
        &self._positions
    }

    // pub fn get_control_point_position(&self) -> &[Float3] {
    //     &self._control_point_position
    // }

    pub fn set_control_point_position(&mut self, index: usize, position: &Float3) {
        self._control_point_position[index] = *position;
    }

    // pub fn get_control_point_normal(&self) -> &[Float3] {
    // 	&self._control_point_normal
    // }

    pub fn get_indices(&self) -> &[u32] {
        &self._indices
    }

    fn update_control_point_normal(&mut self) {
        // ベジエ曲面の各面に以下のインデクスを割り当てる
        // +-+-+-+
        // |0|1|2|
        // |3|4|5|
        // |6|7|8|

        // 各制御点がどの面に影響を受けるかをあらわすインデクス
        let surface_indices = [
            [0, -1, -1, -1],
            [0, 1, -1, -1],
            [1, 2, -1, -1],
            [2, -1, -1, -1],
            [0, 3, -1, -1],
            [0, 1, 3, 4],
            [1, 2, 4, 5],
            [2, 5, -1, -1],
            [3, 6, -1, -1],
            [3, 4, 6, 7],
            [4, 5, 7, 8],
            [5, 7, -1, -1],
            [6, -1, -1, -1],
            [6, 7, -1, -1],
            [7, 8, -1, -1],
            [8, -1, -1, -1],
        ];

        // 各面の法線
        let surface_normals = [
            self.calculate_dot(0, 4, 1),
            self.calculate_dot(1, 5, 2),
            self.calculate_dot(2, 6, 3),
            self.calculate_dot(4, 8, 5),
            self.calculate_dot(5, 9, 6),
            self.calculate_dot(6, 10, 7),
            self.calculate_dot(8, 12, 9),
            self.calculate_dot(9, 13, 10),
            self.calculate_dot(10, 14, 11),
        ];

        // 制御点が属する面の法線の平均を制御店の法線とする
        // 足し込むのですべてゼロ初期化
        for i in 0..self._control_point_normal.len() {
            self._control_point_normal[i] = std::default::Default::default();
        }

        for i in 0..self._control_point_normal.len() {
            for surface_index in surface_indices[i] {
                if surface_index < 0 {
                    continue;
                }

                self._control_point_normal[i].x += surface_normals[surface_index as usize].x;
                self._control_point_normal[i].y += surface_normals[surface_index as usize].y;
                self._control_point_normal[i].z += surface_normals[surface_index as usize].z;

                self._control_point_normal[i].normalize();
            }
        }
    }

    fn calculate_dot(&self, index0: usize, index1: usize, index2: usize) -> Float3 {
        let vector0 = self._control_point_position[index0]
            .direction_to(&self._control_point_position[index1]);
        let vector1 = self._control_point_position[index0]
            .direction_to(&self._control_point_position[index2]);
        let result = vector0.dot(&vector1);
        result
    }

    fn compute_bernstein_polynormal(t: f32, i: u32) -> f32 {
        assert!(0.0 <= t && t <= 1.0);
        assert!(i <= 3); // 3 次

        let n = 3; // 3 次

        // 二項係数
        let binomial_coeeficientes =
            (Self::fractrial(n) as f32) / (Self::fractrial(i) * Self::fractrial(n - i)) as f32;

        let result = binomial_coeeficientes * t.powi(i as i32) * (1.0 - t).powi((n - i) as i32);
        result
    }

    fn fractrial(n: u32) -> u32 {
        match n {
            0 => 1,
            1 => 1,
            _ => Self::fractrial(n - 1) * n,
        }
    }
}

impl Float3 {
    pub fn direction_to(&self, other: &Float3) -> Self {
        Self {
            x: other.x - self.x,
            y: other.y - self.y,
            z: other.z - self.z,
        }
    }

    pub fn normalize(&mut self) {
        let norm = (self.x * self.x + self.y * self.y + self.z * self.z).sqrt();
        self.x /= norm;
        self.y /= norm;
        self.z /= norm;
    }

    pub fn dot(&self, other: &Float3) -> Self {
        Self {
            x: self.y * other.z - other.y * self.z,
            y: -(self.x * other.z - other.x * self.z),
            z: self.x * other.y - other.x * self.y,
        }
    }
}

#[cfg(test)]
pub mod tests {
    #[test]
    fn test() {
        let bu = super::BezierSurface::compute_bernstein_polynormal(0.0, 0);
        let bv = super::BezierSurface::compute_bernstein_polynormal(1.0, 3);
        assert_eq!(bu, 1.0);
        assert_eq!(bv, 1.0);
    }
}
