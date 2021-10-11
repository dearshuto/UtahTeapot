use crate::Float3;

pub struct BezierSurface {
    _control_point_position: [Float3; 16],
    _control_point_normal: [Float3; 16],
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
            _indices: Vec::new(),
        }
    }

    pub fn update(&self, _div: u8, _sub_div: u8) {
        todo!()
    }

    pub fn get_control_point_position(&self) -> &[Float3] {
        &self._control_point_position
    }

    pub fn set_control_point_position(&mut self, index: usize, position: &Float3) {
        self._control_point_position[index] = *position;
    }

    // pub fn get_control_point_normal(&self) -> &[Float3] {
    // 	&self._control_point_normal
    // }

    pub fn get_indices(&self) -> &[u32] {
        &self._indices
    }
}
