set(target ${CUSTOM})

file(GLOB hdrs "*.h*")

add_custom_target(${target} STATIC ${srcs} ${hdrs})