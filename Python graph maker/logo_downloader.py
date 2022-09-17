"""
Downloads Logo from url
"""

import requests
from PIL import Image


def download_logo(url, path):
    """
    Downloads Logo from url and saves it in path
    """
    try:
        response = requests.get(url)
    except requests.exceptions.RequestException as requests_error:
        print(requests_error)
    else:
        with open(path, "wb") as img:
            img.write(response.content)

        with Image.open(path) as img:
            img.resize((300, 300))
