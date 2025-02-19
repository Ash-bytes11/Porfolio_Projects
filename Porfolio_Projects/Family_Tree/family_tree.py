"""
File:    family_tree.py
Author:  Aswanth Jeyaram Kumar

Description:
  This program will make a family by allowing you to enter people, and then query relations between various people in the family tree.
"""


# Define the create function
def create(name, people_dict):
  # Check if the name already exists in the people_dict
  if name in people_dict:
    # If the name already exists, print a message indicating it
    print(f"{name} already exists.")
  else:
    # If the name doesn't exist, create a new entry in the people_dict
    people_dict[name] = {"mother": None, "father": None, "children": []}
    print(f"{name} has been created.")
  return people_dict


# Define the set-mother function
def set_mother(person_name, mother_name, people_dict):
  # Check if the person_name exists in the people_dict
  if person_name not in people_dict:
    print(f"Error: {person_name} does not exist.")
    return

  # Check if the mother_name exists in the people_dict
  if mother_name not in people_dict:
    print(f"Error: {mother_name} does not exist.")
    return

  # Check if the person already has a mother
  if people_dict[person_name]["mother"]:
    print(f"Error: {person_name} already has a mother.")
    return

  # Set the mother for the person by updating the people_dict
  people_dict[person_name]["mother"] = mother_name
  # Add the person as a child to the mother in the people_dict
  people_dict[mother_name]["children"].append(person_name)

  return people_dict


# Define the set-father function
def set_father(person_name, father_name, people_dict):
    # Check if the person_name exists in the people_dict
    if person_name not in people_dict:
        print(f"Error: {person_name} does not exist.")
        return

    # Check if the father_name exists in the people_dict
    if father_name not in people_dict:
        print(f"Error: {father_name} does not exist.")
        return

    # Check if the person already has a father
    if people_dict[person_name]["father"]:
        print(f"Error: {person_name} already has a father.")
        return

    # Set the father for the person by updating the people_dict
    people_dict[person_name]["father"] = father_name
    # Add the person as a child to the father in the people_dict
    people_dict[father_name]["children"].append(person_name)
    return people_dict



# Define the is-ancestor function
def is_ancestor(ancestor_name, person_name, people_dict):
    # Check if the ancestor_name exists in the people_dict
    if ancestor_name not in people_dict:
        # If the ancestor_name doesn't exist, print an error message and return
        print(f"{ancestor_name} does not exist.")
        return

    # Check if the person_name exists in the people_dict
    if person_name not in people_dict:
        # If the person_name doesn't exist, print an error message and return
        print(f"{person_name} does not exist.")
        return

    # Initialize the ancestor_level to 0
    ancestor_level = 0
    # Set the current_person to the person_name
    current_person = person_name

    # Start a loop that continues until a return statement is reached
    while True:
        # Retrieve the mother_name and father_name for the current_person
        mother_name = people_dict[current_person]['mother']
        father_name = people_dict[current_person]['father']

        # Check if the mother_name matches the ancestor_name
        if mother_name == ancestor_name:
            # Check the ancestor_level to determine the relationship description
            if ancestor_level == 0:
                print(f"{ancestor_name} is {person_name}'s mother.")
            else:
                print(
                    f"{ancestor_name} is {person_name}'s {max(0, ancestor_level - 1) * 'great-'}grandmother."
                )
            return

        # Check if the father_name matches the ancestor_name
        if father_name == ancestor_name:
            # Check the ancestor_level to determine the relationship description
            if ancestor_level == 0:
                print(f"{ancestor_name} is {person_name}'s father.")
            else:
                print(
                    f"{ancestor_name} is {person_name}'s {max(0, ancestor_level - 1) * 'great-'}grandfather."
                )
            return

        # Check if all names (ancestor_name, person_name, mother_name, father_name) are the same
        if mother_name == father_name == ancestor_name == person_name:
            print(f"{ancestor_name} is {person_name}'s ancestor.")
            return

        # Check if both mother_name and father_name match the ancestor_name
        if mother_name == father_name == ancestor_name:
            # Recursively call is_ancestor to determine if ancestor_name is a great-grandparent
            if is_ancestor(ancestor_name, mother_name, people_dict):
                print(
                    f"{ancestor_name} is {person_name}'s {max(0, ancestor_level - 1) * 'great-'}great-grandparent."
                )
            return

        # Check if mother_name matches the ancestor_name
        if mother_name == ancestor_name:
            # Recursively call is_ancestor to determine if ancestor_name is a grandmother
            if is_ancestor(ancestor_name, mother_name, people_dict):
                # Check the ancestor_level to determine the relationship description
                if ancestor_level == 0:
                    print(f"{mother_name} is {person_name}'s mother.")
                else:
                    print(
                        f"{ancestor_name} is {person_name}'s {max(0, ancestor_level - 1) * 'great-'}grandmother."
                    )
                return

        # Check if father_name matches the ancestor_name
        if father_name == ancestor_name:
            # Recursively call is_ancestor to determine if ancestor_name is a grandfather
            if is_ancestor(ancestor_name, father_name, people_dict):
                # Check the ancestor_level to determine the relationship description
                if ancestor_level == 0:
                    print(f"{father_name} is {person_name}'s father.")
                else:
                    print(
                        f"{ancestor_name} is {person_name}'s {max(0, ancestor_level - 1) * 'great-'}grandfather."
                    )
                return

        # Check if both mother_name and father_name are None
        if mother_name == father_name == None:
            print(f"{ancestor_name} is not {person_name}'s ancestor.")
            return

        # Increment the ancestor_level
        ancestor_level += 1
        # Update the current_person based on the relationship
        if mother_name == ancestor_name:
            current_person = mother_name
        elif father_name == ancestor_name:
            current_person = father_name
        else:
            current_person = mother_name if mother_name else father_name



# Define the is-descendant function
def is_descendant(descendant_name, person_name, people_dict):
    # Check if the descendant_name exists in the people_dict
    if descendant_name not in people_dict:
        print(f"{descendant_name} does not exist.")
        return False

    # Check if the person_name exists in the people_dict
    if person_name not in people_dict:
        print(f"{person_name} does not exist.")
        return False

    # Define a helper function to recursively check if descendant_name is a descendant of person_name
    def check_descendant(descendant_name, person_name):
        person = people_dict[person_name]

        # Check if the descendant_name matches the mother or father of the person
        if person["mother"] == descendant_name or person["father"] == descendant_name:
            return True

        # Recursively call check_descendant for the mother and father of the person
        if person["mother"] and check_descendant(descendant_name, person["mother"]):
            return True
        if person["father"] and check_descendant(descendant_name, person["father"]):
            return True

        # If no match is found, return False
        return False

    # Call the check_descendant function with the descendant_name and person_name
    if check_descendant(descendant_name, person_name):
        print(f"Yes, {person_name} is a descendant of {descendant_name}.")
        return True
    else:
        print(f"No, {person_name} is not a descendant of {descendant_name}.")
        return False



# Define the display-person function
def display_person(name, people_dict):
    # Check if the name exists in the people_dict
    if name not in people_dict:
        print(f"{name} does not exist.")
        return

    # Get the person's data from the people_dict
    person = people_dict[name]
    
    # Get the mother's name, or "None Listed" if not available
    mother = person.get("mother", "None Listed")
    
    # Get the father's name, or "None Listed" if not available
    father = person.get("father", "None Listed")
    
    # Find the children's names for the current person
    children = [
        child_name for child_name, child_data in people_dict.items()
        if (child_data.get("mother") == name or child_data.get("father") == name)
    ]

    # Print the person's information
    print(f"{name}")
    print(f"    Mother: {mother}, Father: {father}")
    if children:
        children_names = ", ".join(children)
        print(f"    Children: {children_names}")
    else:
        print("    Children: None Listed")



# Define the display-people function
def display_people(people_dict):
    # Iterate over each person and their info in the people_dict
    for person, info in people_dict.items():
        # Get the mother's name, or "None Listed" if not available
        mother = info.get('mother', "None Listed")
        
        # Get the father's name, or "None Listed" if not available
        father = info.get('father', "None Listed")
        
        # Get the list of children's names, or an empty list if not available
        children = ", ".join(info.get('children', []))

        # Print the person's information
        print(
            f"{person}\n\tMother: {mother}, Father: {father}\n\tChildren: {children}"
        )



# Define the save function
def save(filename, people_dict):
    # Open the file in write mode
    with open(filename, "w") as file:
        # Iterate over each person and their info in the people_dict
        for name, info in people_dict.items():
            # Get the mother's name, or "None" if not available
            mother_name = info.get("mother", "None")
            
            # Get the father's name, or "None" if not available
            father_name = info.get("father", "None")
            
            # Get the list of children's names as a comma-separated string, or an empty string if not available
            children_names = ",".join(info.get("children", []))
            
            # Write the person's information to the file in CSV format
            file.write(f"{name},{mother_name},{father_name},{children_names}\n")

    # Print a confirmation message
    print("Data has been saved to the file.")



# Define the load function
def load(filename, people_dict):
    # Open the file in read mode
    with open(filename, "r") as file:
        # Iterate over each line in the file
        for line in file:
            # Strip the whitespace and split the line into individual values
            line = line.strip()
            values = line.split(",")

            # Get all the names from the list
            name = values[0]
            mother_name = values[1]
            father_name = values[2]
            children_names = values[3:]

            # Handle the case where mother or father names are "None"
            mother_name = mother_name if mother_name != "None" else None
            father_name = father_name if father_name != "None" else None

            # Create a new entry in people_dict for the person
            people_dict[name] = {
                "mother": mother_name,
                "father": father_name,
                "children": children_names
            }

            # Add the person to their parents' children list, if applicable
            if mother_name:
                if mother_name not in people_dict:
                    people_dict[mother_name] = {
                        "mother": None,
                        "father": None,
                        "children": []
                    }

            if father_name:
                if father_name not in people_dict:
                    people_dict[father_name] = {
                        "mother": None,
                        "father": None,
                        "children": []
                    }

    # Print a confirmation message
    print("Data has been loaded from the file.")

    # Returns the dictionary
    return people_dict



# Define the is-cousin function
def is_cousin(person_name, other_person_name, people_dict):
    # Check if person_name and other_person_name are the same person
    if person_name == other_person_name:
        print(f"{person_name} and {other_person_name} are the same person.")
        return False

    # Get the parents of person_name and other_person_name from the people_dict
    person_parents = people_dict.get(person_name, [])
    other_person_parents = people_dict.get(other_person_name, [])

    # Iterate over the parents of person_name
    for parent in person_parents:
        # Check if the parent is also a parent of other_person_name
        if parent in other_person_parents:
            print("They are 1-cousins, 0 times removed")
            return True

        # Iterate over the grandparents of the parent
        for grandparent in people_dict.get(parent, []):
            # Recursively call is_cousin with grandparent and other_person_name
            if is_cousin(grandparent, other_person_name, people_dict):
                # Determine the removed count based on the relationship between person_name and grandparent
                if person_name in people_dict[grandparent]:
                    removed_count = get_removed_count(person_name, grandparent, people_dict)
                else:
                    removed_count = get_removed_count(other_person_name, grandparent, people_dict)
                print(f"They are {removed_count}-cousins, {removed_count} times removed")
                return True

    # If no cousin relationship is found, print the message and return False
    print(f"{person_name} and {other_person_name} are not cousins.")
    return False


def get_removed_count(person_name, ancestor_name, people_dict, count=0):
    # Check if person_name is the ancestor_name
    if person_name == ancestor_name:
        return count

    # Get the parents of person_name
    person_parents = people_dict.get(person_name, [])

    # Iterate over the parents and increment the count
    for parent in person_parents:
        count += 1
        # Recursively call get_removed_count with parent and ancestor_name
        return get_removed_count(parent, ancestor_name, people_dict, count)

    return None



if __name__ == "__main__":
  # Create an empty dictionary to store people's information
  people_dict = {}

  # Get the user input
  user_input = input(">> ")
  while user_input != "exit":
    # Split the user input into its components
    input_list = user_input.split()

    # Call the appropriate function based on the command
    command = input_list[0]
    if command == "create":
      name = input_list[1]
      create(name, people_dict)
    elif command == "set-mother":
      person_name = input_list[1]
      mother_name = input_list[2]
      set_mother(person_name, mother_name, people_dict)
    elif command == "set-father":
      person_name = input_list[1]
      father_name = input_list[2]
      set_father(person_name, father_name, people_dict)
    elif command == "is-ancestor":
      ancestor_name = input_list[1]
      person_name = input_list[2]
      is_ancestor(ancestor_name, person_name, people_dict)
    elif command == "is-descendant":
      descendant_name = input_list[2]
      person_name = input_list[1]
      is_descendant(descendant_name, person_name, people_dict)
    elif command == "display-person":
      name = input_list[1]
      display_person(name, people_dict)
    elif command == "display-people":
      display_people(people_dict)
    elif command == "save":
      filename = input_list[1]
      save(filename, people_dict)
    elif command == "load":
      filename = input_list[1]
      load(filename, people_dict)
    elif command == "is-cousin":
      person_name = input_list[1]
      other_person_name = input_list[2]
      is_cousin(person_name, other_person_name, people_dict)
    else:
      print("Invalid command.")

    # Get the next user input
    user_input = input(">> ")
