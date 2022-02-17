extern crate kiss3d;
extern crate nalgebra as na;

use std::cell::RefCell;
use std::rc::Rc;
use clap::Parser;
use kiss3d::light::Light;
use kiss3d::resource::Mesh;
use kiss3d::scene::SceneNode;
use kiss3d::window::{State, Window};
use na::{UnitQuaternion, Vector3, Point3};

#[derive(Parser, Debug)]
#[clap(author, version, about)]
struct Args {
    #[clap(short = 'x', long = "div", default_value_t = 4)]
    div: u8,

    #[clap(short = 'y', long = "sub-div", default_value_t = 4)]
    sub_div: u8,
}

struct AppState {
    c: SceneNode,
    rot: UnitQuaternion<f32>,
}

impl State for AppState {
    fn step(&mut self, _: &mut Window) {
        self.c.prepend_to_local_rotation(&self.rot)
    }
}

fn main() {
    let args = Args::parse();

    let mut utar_teapot = ut::UtahTeapot::new();
    utar_teapot.update_clockwise(args.div, args.sub_div);

    let mut window = Window::new("Utar Teapot preview example");

    // Z-up に無理やり変換
    let vertices: Vec<Point3<f32>> = utar_teapot.get_positions().iter().map(|x| Point3::new(x.x, x.z, x.y)).collect();
    let indices: Vec<Point3<u16>> = utar_teapot.get_indices().chunks(3).map(|x| Point3::new(x[0] as u16, x[1] as u16, x[2] as u16)).collect();

    let mesh = Rc::new(RefCell::new(Mesh::new(
        vertices, indices, None, None, false,
    )));
    let mut c = window.add_mesh(mesh, Vector3::new(1.0, 1.0, 1.0));

    c.set_color(1.0, 1.0, 1.0);

    window.set_light(Light::StickToCamera);

    let rot = UnitQuaternion::from_axis_angle(&Vector3::y_axis(), 0.014);
    let state = AppState { c, rot };

    window.render_loop(state)
}
