let root = Sys.getenv("cur__root");
let c_flags = ["-I", Filename.concat(root, "include/glm")]

let flags = [];

let cxx_flags = c_flags @ ["-fno-exceptions", "-fPIC", "-fno-rtti", "-lstdc++"]

Configurator.V1.Flags.write_sexp("c_flags.sexp", c_flags);
Configurator.V1.Flags.write_sexp("cxx_flags.sexp", cxx_flags);
Configurator.V1.Flags.write_sexp("flags.sexp", flags);