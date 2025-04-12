#!/bin/bash
#
# Generate a new component by:
#   Copy all files in current directory to component name directory
#   Change the ../component filenames to the provided component name
#

read -p "Enter the component's name: " component_name
read -p "Select the code directory (1 for sample_app, 2 for sample_lib): " code_dir_choice

COMPONENT_NAME_LOWER="$component_name"
COMPONENT_NAME_FIRST="$(echo "$component_name" | sed 's/.*/\u&/')"
COMPONENT_NAME_UPPER="$(echo "$component_name" | tr '[:lower:]' '[:upper:]')"

SCRIPT_DIR=$(cd `dirname $0` && pwd)

if [ "$code_dir_choice" -eq 1 ]; then
    CODE_DIR=./sample_app
elif [ "$code_dir_choice" -eq 2 ]; then
    CODE_DIR=./sample_lib
else
    echo "Invalid choice. Exiting."
    exit 1
fi

NEW_DIR=./${COMPONENT_NAME_LOWER}

# Debugging
cp -R $CODE_DIR $NEW_DIR
echo ""

SAMPLE_NAME_LOWER="sample"
SAMPLE_NAME_FIRST="Sample"
SAMPLE_NAME_UPPER="SAMPLE"

# Loop through each file in the search directory
find "$NEW_DIR" -type f | while IFS= read -r file; do
    # Perform the replacements in the file
    sed -i "s/$SAMPLE_NAME_LOWER/$COMPONENT_NAME_LOWER/g" "$file"
    sed -i "s/$SAMPLE_NAME_FIRST/$COMPONENT_NAME_FIRST/g" "$file"
    sed -i "s/$SAMPLE_NAME_UPPER/$COMPONENT_NAME_UPPER/g" "$file"
    
    # Rename the file if necessary
    new_filename=$(echo "$file" | sed -e "s/$SAMPLE_NAME_LOWER/$COMPONENT_NAME_LOWER/g" -e "s/$SAMPLE_NAME_FIRST/$COMPONENT_NAME_FIRST/g" -e "s/$SAMPLE_NAME_UPPER/$COMPONENT_NAME_UPPER/g")
    if [ "$file" != "$new_filename" ]; then
        mv "$file" "$new_filename"
    fi
done

if [ "$code_dir_choice" -eq 1 ]; then
    COMPONENT_TARGET="${COMPONENT_NAME_LOWER}"
    cp -r $COMPONENT_NAME_LOWER ../../apps/$COMPONENT_TARGET && rm -rf $COMPONENT_NAME_LOWER
elif [ "$code_dir_choice" -eq 2 ]; then
    COMPONENT_TARGET="${COMPONENT_NAME_LOWER}_lib"
    cp -r $COMPONENT_NAME_LOWER ../../libs/$COMPONENT_TARGET && rm -rf $COMPONENT_NAME_LOWER
else
    echo "Invalid choice. Exiting."
    exit 1
fi

echo "generate_template.sh complete!"