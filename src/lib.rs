mod bezier_surface;
use self::bezier_surface::BezierSurface;

mod common;

#[derive(Clone, Copy, Default, Debug)]
pub struct Float3 {
    pub x: f32,
    pub y: f32,
    pub z: f32,
}

pub struct UtahTeapot {
    _positions: Vec<Float3>,
    _normals: Vec<Float3>,
    _indices: Vec<u32>,
}

impl UtahTeapot {
    pub fn new() -> Self {
        Self {
            _positions: Vec::new(),
            _normals: Vec::new(),
            _indices: Vec::new(),
        }
    }

    pub fn new_with_div(_div: u8, _sub_div: u8) -> Self {
        todo!()
    }

    pub fn update(&mut self, div: u8, sub_div: u8) {
        let index_stride = 0u32;
        for indices in self::common::UTA_TEAPOT_INDICES {
            let mut bezier_surface = BezierSurface::new();
            for i in 0..indices.len() {
                let index = indices[i] - 1;
                let vertex = &self::common::UTAH_TEAPOT_VERTICES[index as usize];
                bezier_surface.set_control_point_position(
                    i,
                    &Float3 {
                        x: vertex[0],
                        y: vertex[1],
                        z: vertex[2],
                    },
                )
            }

            bezier_surface.update(div, sub_div);

            // 頂点情報
            for index in bezier_surface.get_indices() {
                let vertex = &bezier_surface.get_control_point_position()[*index as usize];
                self._positions.push(*vertex);
            }

            // インデクス情報
            for i in 0..(bezier_surface.get_indices().len() as u32 / 4) {
                self._indices.push(index_stride + 4 * i + 0);
                self._indices.push(index_stride + 4 * i + 1);
                self._indices.push(index_stride + 4 * i + 2);
                self._indices.push(index_stride + 4 * i + 3);
            }
        }
    }

    pub fn get_positions(&self) -> &[Float3] {
        &self._positions
    }

    pub fn get_normals(&self) -> &[Float3] {
        &self._normals
    }

    pub fn get_indices(&self) -> &[u32] {
        &self._indices
    }
}
