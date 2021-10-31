use crate::UtahTeapot;

#[no_mangle]
pub extern "C" fn create_instance() -> *mut UtahTeapot {
    Box::into_raw(Box::new(UtahTeapot::new()))
}

#[no_mangle]
pub extern "C" fn destroy_instance(ptr: *mut UtahTeapot) {
    unsafe { Box::from_raw(ptr) };
}

#[no_mangle]
pub extern "C" fn update(ptr: *mut UtahTeapot, div: u8, sub_div: u8) {
    unsafe {
        (*ptr).update_clockwise(div, sub_div);
    }
}

#[no_mangle]
pub extern "C" fn get_vertex_count(ptr: *const UtahTeapot) -> usize {
    unsafe { (*ptr).get_positions().len() }
}

#[no_mangle]
pub extern "C" fn get_position(
    ptr: *const UtahTeapot,
    x: &mut f32,
    y: &mut f32,
    z: &mut f32,
    index: usize,
) {
    unsafe {
        let position = (*ptr).get_positions()[index];
        *x = position.x;
        *y = position.y;
        *z = position.z;
    }
}

#[no_mangle]
pub extern "C" fn get_normal(
    ptr: *const UtahTeapot,
    x: &mut f32,
    y: &mut f32,
    z: &mut f32,
    index: usize,
) {
    unsafe {
        let normal = (*ptr).get_normals()[index];
        *x = normal.x;
        *y = normal.y;
        *z = normal.z;
    }
}

#[no_mangle]
pub extern "C" fn get_index_count(ptr: *const UtahTeapot) -> usize {
    unsafe { (*ptr).get_indices().len() }
}

#[no_mangle]
pub extern "C" fn get_index(ptr: *const UtahTeapot, index: usize) -> u32 {
    unsafe { (*ptr).get_indices()[index] }
}
