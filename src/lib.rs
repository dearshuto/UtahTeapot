mod bezier_surface;
use self::bezier_surface::BezierSurface;

mod common;

#[derive(Clone, Copy, Debug)]
enum FrontFace {
    Clockwise,
    CounterClockwise,
}

#[derive(Clone, Copy, Default, Debug)]
pub struct Float2 {
    pub x: f32,
    pub y: f32,
}

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

    #[deprecated]
    pub fn update(&mut self, div: u8, sub_div: u8) {
        self.update_impl(div, sub_div, FrontFace::CounterClockwise);
    }

    pub fn update_clockwise(&mut self, div: u8, sub_div: u8) {
        self.update_impl(div, sub_div, FrontFace::Clockwise);
    }

    pub fn update_counter_clockwise(&mut self, div: u8, sub_div: u8) {
        self.update_impl(div, sub_div, FrontFace::CounterClockwise);
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

    fn update_impl(&mut self, div: u8, sub_div: u8, front_face: FrontFace) {
        let mut index_stride = 0u32;
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

            bezier_surface.update(div, sub_div, front_face);

            // 頂点情報
            for index in bezier_surface.get_indices() {
                let vertex = &bezier_surface.get_positions()[*index as usize];
                self._positions.push(*vertex);

                let normal = &bezier_surface.get_normals()[*index as usize];
                self._normals.push(*normal);
            }

            // インデクス情報
            match front_face {
                FrontFace::Clockwise => {
                    for i in 0..(bezier_surface.get_indices().len() as u32 / 3) {
                        self._indices.push(index_stride + 3 * i + 0);
                        self._indices.push(index_stride + 3 * i + 2);
                        self._indices.push(index_stride + 3 * i + 1);
                    }
                }
                FrontFace::CounterClockwise => {
                    for i in 0..(bezier_surface.get_indices().len() as u32 / 3) {
                        self._indices.push(index_stride + 3 * i + 0);
                        self._indices.push(index_stride + 3 * i + 1);
                        self._indices.push(index_stride + 3 * i + 2);
                    }
                }
            }

            index_stride += bezier_surface.get_indices().len() as u32;
        }
    }
}
