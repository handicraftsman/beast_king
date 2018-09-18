#include <particlepm.hpp>

#include "beast_king/version.hpp"

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("beast_king");
  p->version(PPM::Version(BEAST_KING_VERSION));
  p->description("A king for Beast applications");
  p->github(PPM::GitHub("handicraftsman", "beast_king"));
  p->license(PPM::License("MIT", "https://github.com/handicraftsman/beast_king/blob/master/LICENSE.txt"));

  PPM::libs.insert("boost_system");
  PPM::libs.insert("boost_log");
  PPM::libs.insert("boost_log_setup");
  PPM::libs.insert("boost_thread");
  PPM::libs.insert("boost_filesystem");
  PPM::libs.insert("boost_regex");
  PPM::libs.insert("skyr");

  PPM::TargetPtr lib = p->library("beast_king");
  lib->cpp("gnu++17");
  lib->cpp_files({
    "beast_king/app.cpp",
    "beast_king/context.cpp",
    "beast_king/router.cpp",
    "beast_king/server.cpp",
    "beast_king/simple_router.cpp"
  });
  lib->cpp_flags(
    flagcat({
      ("-L" + PPM::dist_dir),

      "-lboost_system",
      "-lboost_log",
      "-lboost_log_setup",
      "-lboost_thread",
      "-lskyr",

      ("-I" + p->pkg_dir())
    })
  );

  PPM::TargetPtr threaded_s = p->library("beast_king_server_threaded");
  threaded_s->cpp("gnu++17");
  threaded_s->cpp_files({
    "beast_king/server_threaded.cpp"
  });
  threaded_s->cpp_flags(
    flagcat({
      ("-L" + PPM::dist_dir),

      "-lbeast_king",
      "-lboost_system",
      "-lboost_thread",
      
      ("-I" + p->pkg_dir()),

      "-pthread"
    })
  );

  if (PPM::dev) {
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

        "-pthread"
      })
    );
    exe->depends(lib);
  }

}