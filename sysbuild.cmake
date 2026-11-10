#
# Share the app's board overlay (partition layout) with the other images,
# sysbuild only applies boards/*.overlay to the main project image automatically.
#

zephyr_build_string(board_string BOARD ${BOARD} BOARD_QUALIFIERS ${BOARD_QUALIFIERS})
set(board_overlay ${CMAKE_CURRENT_LIST_DIR}/boards/${board_string}.overlay)

if(EXISTS ${board_overlay})
  foreach(image mcuboot ${SB_CONFIG_BM_FIRMWARE_LOADER_IMAGE_NAME} installer)
    if(TARGET ${image})
      add_overlay_dts(${image} ${board_overlay})
    endif()
  endforeach()
endif()
