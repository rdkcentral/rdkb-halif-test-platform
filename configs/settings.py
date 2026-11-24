'''
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
'''

"""Platform-owned defaults and registration for the shared controller."""
import os
from pathlib import Path
from framework.configuration import Component
from framework import execution


def create_component(controller_root):
    root = Path(controller_root)

    def executable(filename):
        for directory in (root / "build-run", root / "install-run/bin"):
            candidate = directory / filename
            if candidate.is_file() and os.access(candidate, os.X_OK):
                return candidate
        return root / "build-run" / filename

    return Component(
        name="platform", profile=root / "configs/platform_hal.json",
        cli=os.environ.get("PLATFORM_VL_DUT_CLI") or str(executable("platform_vl_cli")),
        server=Path(os.environ.get("PLATFORM_VL_SERVER") or executable("platform_vl")).expanduser(),
        socket_path=os.environ.get("PLATFORM_VL_SOCKET_PATH") or "/tmp/platform_vl-run.sock",
        log=root / "logs/platform/backend.log",
        command_builder=execution.build_command, readiness=execution.responsive,
        startup=execution.startup, preflight=execution.preflight,
        options={"selector": "--platform-api", "magic": 0x50564c31},
    )
