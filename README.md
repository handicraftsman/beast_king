# BeastKing

A web framework based on Boost.Beast.

## Installing

This is the particlepm manifest which can be used to build the example app from this repository:

```cpp

PPM_PACKAGE(p) {  
  // package definition  

  PPM::GitHubPtr bk = p->github_repo("handicraftsman", "beast_king");

  PPM::TargetPtr exe = p->executable("bk-test");
  exe->cpp("gnu++17");
  exe->cpp_files({
    "bk-test/main.cpp",
    "bk-test/app.cpp"
  });
  exe->cpp_flags(
    flagcat({
      ("-L" + PPM::dist_dir),

      "-lboost_system",
      "-lboost_log",
      "-lboost_log_setup",
      "-lboost_thread",

      "-lbeast_king",
      "-lbeast_king_server_threaded",

      ("-I" + p->pkg_dir()),
      ("-I" + bk->dir()),

      "-pthread"
    })
  );
  exe->depends(lib);

}
```

## Dependencies

This library depends on Boost>=1.66 and [URL](https://github.com/glynos/url)

You can configure paths to them using ParticlePM environment files as described [here](https://github.com/handicraftsman/particlepm).

Warning: URL library must be cloned with the `--recursive` flag and built with `-DBUILD_SHARED_LIBS=ON` flag.

## C++ version

This library uses GNU C++17 and may require using GCC 8 for building.

## Servers and routers

BeastKing allows using custom servers and routers - you pass your app instance to a server and app stores a pointer to a router.

Other servers and routers can be received from other particlepm packages (if any) or written manually.