SET(SOURCES ui_Main.c
    ui_Payment.c
    ui_Preparation.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    ui_img_images_img_price_png.c
    ui_img_images_img_espresso_png.c
    ui_img_images_img_latte_png.c
    ui_img_images_img_irish_coffee_png.c
    ui_img_images_logo_png.c
    ui_img_images_img_devider_png.c
    ui_img_images_button_back_png.c
    ui_img_images_icon_card_png.c
    ui_img_images_coffee_png.c
    ui_img_images_mask_png.c
    ui_img_images_empty_glass_png.c
    fonts/ui_font_in20.c
    fonts/ui_font_in25.c
    fonts/ui_font_in30.c)

add_library(ui ${SOURCES})
