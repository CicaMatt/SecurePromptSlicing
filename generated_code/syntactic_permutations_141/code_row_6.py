import streamlit as st
from PIL import Image

def main():
    image = Image.open('image_path')
    st.image(image, caption='Image', use_column_width=True)

if __name__ == '__main__':
    main()