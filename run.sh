echo
# Install graphviz and add to path
echo "Installing graphviz..."
sudo apt-get install graphviz
echo "Done."

echo
# install all required packages
echo "Installing required packages..."
pip install -r requirements.txt
echo "Done."