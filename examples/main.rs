fn main() {
    let mut utah_teapot = ut::UtahTeapot::new();
    utah_teapot.update(10, 10);

    for position in utah_teapot.get_positions() {
        println!("{}, {}, {}", position.x, position.y, position.z);
    }

    for index in utah_teapot.get_indices() {
        println!("{}", index);
    }
}
