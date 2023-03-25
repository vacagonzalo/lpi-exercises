use std::fs::File;
use std::io::{self, Read, Write};
use std::{env, process};

struct Config {
    create_file: bool,
    file_path: String,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("Usage: rtee -n file | rtee -a file");
        }
        let create_file = "-n" == args[1];
        let file_path = args[2].clone();
        Ok(Config {
            create_file,
            file_path,
        })
    }
}

fn run(config: &Config) -> i32 {
    println!("{} {}", config.create_file, config.file_path);
    let mut file = File::create(config.file_path.clone()).expect("could not create the file");
    let mut buffer = [0; 1024];
    let num_read = io::stdin().read(&mut buffer).unwrap();
    io::stdout().write_all(&buffer[..num_read]).unwrap();
    file.write(&buffer[..num_read]).expect("fail to write in file");
    return 0;
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let config = Config::build(&args).unwrap_or_else(|err| {
        eprintln!("{err}");
        process::exit(1);
    });
    run(&config);
}
