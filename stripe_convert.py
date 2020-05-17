import png

EMOJI_PX = 72

r = png.Reader(open('emoji_1.png', 'rb'))
width, height, data, info = r.asRGBA()

pixels_rows = list(data)

new_pixels = []

print(width, height)

for row in range(height // EMOJI_PX):
    for col in range(width // EMOJI_PX):
        for px in range(EMOJI_PX):
            new_pixels.append(
                pixels_rows[row * EMOJI_PX + px][(col * EMOJI_PX * 4):(col * EMOJI_PX * 4 + EMOJI_PX * 4)]
            )

png.from_array(new_pixels, 'RGBA').save('emoji_1_colun.png')
