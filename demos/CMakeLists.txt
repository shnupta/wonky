function (make_demo NAME)
	add_executable(${NAME} ${NAME}.cc)
	target_link_libraries(${NAME} wonky::wonky)
endfunction()

make_demo(full_screen)

