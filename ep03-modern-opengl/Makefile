BUILD_DIR = build

default: build

${BUILD_DIR}/build.ninja:
	meson setup ${BUILD_DIR}

.PHONY: clean reset build run
clean:
	ninja -C ${BUILD_DIR} clean

reset:
	meson setup --wipe ${BUILD_DIR}

build: | ${BUILD_DIR}/build.ninja
	ninja -C ${BUILD_DIR}

run:
	${BUILD_DIR}/app
