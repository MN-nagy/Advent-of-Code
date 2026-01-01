use std::collections::HashMap;

struct Solution {}

#[allow(dead_code)]
impl Solution {
    pub fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
        let mut idx: HashMap<i32, usize> = HashMap::new();

        for i in 0..nums.len() {
            let comp: i32 = target - nums[i];

            if let Some(&k) = idx.get(&comp) {
                return vec![k as i32, i as i32];
            }

            idx.insert(nums[i], i);
        }

        vec![0, 0]
    }
}

fn main() {
    println!("hello rust");
}
