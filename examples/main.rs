use clap::{App, Arg};
use std::vec;

fn main() {
    let matches = App::new("UtahTeapot")
        .arg(
            Arg::new("div")
                .short('x')
                .takes_value(true)
                .required(true)
                .max_values(255),
        )
        .arg(
            Arg::new("subdiv")
                .short('y')
                .takes_value(true)
                .required(true)
                .max_values(255),
        )
        .get_matches();

    let div = matches.value_of("div").unwrap().parse::<u8>().unwrap();
    let sub_div = matches.value_of("subdiv").unwrap().parse::<u8>().unwrap();

    let mut utah_teapot = ut::UtahTeapot::new();
    utah_teapot.update_clockwise(div, sub_div);

    let set = obj_exporter::ObjSet {
        material_library: None,
        objects: vec![obj_exporter::Object {
            name: "UtahTeapot".to_owned(),
            vertices: utah_teapot
                .get_positions()
                .into_iter()
                .map(|x| obj_exporter::Vertex {
                    x: x.x as f64,
                    y: x.y as f64,
                    z: x.z as f64,
                })
                .collect(),
            tex_vertices: vec![],
            normals: vec![],
            geometry: vec![obj_exporter::Geometry {
                material_name: None,
                shapes: (0..utah_teapot.get_indices().len() / 3)
                    .into_iter()
                    .map(|index| {
                        let i0 = utah_teapot.get_indices()[3 * index + 0] as usize;
                        let i1 = utah_teapot.get_indices()[3 * index + 1] as usize;
                        let i2 = utah_teapot.get_indices()[3 * index + 2] as usize;
                        obj_exporter::Shape {
                            primitive: obj_exporter::Primitive::Triangle(
                                (i0, Some(i0), Some(0)),
                                (i1, Some(i1), Some(0)),
                                (i2, Some(i2), Some(0)),
                            ),
                            groups: vec![],
                            smoothing_groups: vec![],
                        }
                    })
                    .collect(),
            }],
        }],
    };
    obj_exporter::export_to_file(&set, "utah_teapot.obj").unwrap();
}
