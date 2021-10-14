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
        self._indices.clear();
        self._positions.clear();
        self._normals.clear();

        // 縦横の超点数
        // 両端に頂点があるので +2 してます
        let n_count = div + 2;
        let m_count = sub_div + 2;

        let mut uv = Vec::<Float2>::new();
        uv.resize((n_count * m_count) as usize, Float2::default());
        self._positions
            .resize((n_count * m_count) as usize, Float3::default());

        let stride_u = 1.0 / (div + 1) as f32;
        let stride_v = 1.0 / (sub_div + 1) as f32;

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


#[cfg(test)]
pub mod tests
{
	#[test]
	fn test()
	{
		let bu = super::BezierSurface::compute_bernstein_polynormal(0.0, 0);
		let bv = super::BezierSurface::compute_bernstein_polynormal(1.0, 3);
		assert_eq!(bu, 1.0);
		assert_eq!(bv, 1.0);
	}
}
