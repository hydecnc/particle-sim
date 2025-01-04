from PIL import Image

with open("./particle_pos.txt") as file:
    content = file.read()
    particle_pos = content.split("), (")

particle_pos[0] = particle_pos[0][1:]
particle_pos[-1] = particle_pos[-1].strip()[:-2]

new_width = 800
new_height = 800

image = Image.open("./logo.jpg")
image = image.convert("RGB")
image = image.resize((new_width, new_height))


result_color = []

pos_to_color = image.load()
for particle in particle_pos:
    x, y = particle.split(", ")
    x = (float(x) + 1) / 2
    y = 1 - (float(y) + 1) / 2
    x = x * (new_width - 1)
    y = y * (new_height - 1)

    x = round(x)
    y = round(y)
    result_color.append(pos_to_color[(x, y)])

print("{", end="")
for color in result_color:
    # print(f"{{{color[0] }, {color[1] }, {color[2] }}}", end=", ")
    print(
        f"{{{round(color[0] / 255, 8)}, {round(color[1] / 255, 8)}, {round(color[2] / 255, 8)}}}",
        end=", ",
    )
print("}")
