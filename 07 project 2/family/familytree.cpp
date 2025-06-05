/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Tekniikat / Programming 2: Techniques          #
# Project: Suku on pahin / All in the family                                #
# File: familytree.cpp                                                      #
# Description: Familytree functions                                         #
#   Contains necssary implementations for the functions to be executed      #
#   for relevant commands as per the requirement of the project             #
#                                                                           #
#   Program author ( Fill with your own info )                              #
#   Name: Rong Guo, Pechchuma Manoharan                                     #
#   Student number: 152688192, 153064090                                    #
#   UserID: mcc996, mpp349 ( Necessary due to gitlab folder naming )        #
#   E-Mail: rong.guo@tuni.fi, pechchuma.manoharan@tuni.fi                   #
#############################################################################
*/
#include "familytree.hh"
#include "cli.hh"
#include <iostream>
#include <vector>

Familytree::Familytree()
{

}


// Add Person to be stored in memory
void Familytree::addNewPerson(const std::string &id, int height,
                              std::ostream &output)
{
    // Using getPointer to check if the person already exists,
    // then print error
    if (getPointer(id) != nullptr)
    {
        output << ALREADY_ADDED << std::endl;
        return;
    }

    //Reserve memory for new person
    data_[id] = std::make_shared<Person>
            (Person{id, height, {nullptr, nullptr}, {}});
}


// Add parent-child relationship
void Familytree::addRelation(const std::string &child,
                             const std::vector<std::string>
                             &parents, std::ostream &output)
{
    // For children

    // Using getPointer to check if the child exists
    Person* child_ptr = getPointer(child);
    if (child_ptr == nullptr)
    {
        printNotFound(child, output);
        return;
    }

    // For parents

    for ( unsigned int i = 0; i < parents.size(); ++i )
    {
        // Using getPointer to check if the parent exists
         Person* parent_ptr = getPointer(parents.at(i));

         if (parent_ptr == nullptr)
         {
             continue;
         }

        // Build parent-child relationship in both directions
         // Assign parent
         child_ptr->parents_.at(i) = parent_ptr;

         // Add child to parent's children vector
         parent_ptr->children_.push_back(child_ptr);
    }
}


// Print all persons in the family tree from input file
void Familytree::printPersons(Params, std::ostream &output) const
{

    for (const auto& entry : data_)
    {
        // Using getPointer to get Person object
        Person* person = getPointer(entry.first);  // Using the ID from the map

        // Check if the person exists
        if (person != nullptr)
        {
            output << person->id_ << ", " << person->height_ << std::endl;
        }
    }
}


// Prints children of input person
void Familytree::printChildren(Params params,
                               std::ostream &output) const
{
    // To get the person's ID
    StrRef parent_id = params.at(0);
    Person* parent = getPointer(parent_id);

    // Check if the person exists, then print
    if ( parent == nullptr )
    {
        printNotFound(parent_id, output);
        return;
    }

    IdSet childIds;
    for ( const auto& child_ptr : parent->children_)
    {
        childIds.insert(child_ptr->id_);
    }

    printGroup(parent_id, "children", childIds, output);

}


// Prints parents of input person
void Familytree::printParents(Params params,
                              std::ostream &output) const
{
    StrRef child_id = params.at(0);
    Person* child = getPointer(child_id);

    // Check if the person exists, then print
    if ( child == nullptr )
    {
        printNotFound(child_id, output);
        return;
    }

    IdSet parentIds;
    for ( const auto& parent_ptr : child->parents_)
    {
        // If the child has parents,
        if ( parent_ptr != nullptr)
        {
            parentIds.insert(parent_ptr->id_);
        }
    }

    printGroup(child_id, "parents", parentIds, output);
}


// Prints siblings of input person
void Familytree::printSiblings(Params params,
                               std::ostream &output) const
{
    StrRef child_id = params.at(0);
    Person* child = getPointer(child_id);

    // Check if the person exists, then print
    if ( child == nullptr )
    {
        printNotFound(child_id, output);
        return;
    }

    IdSet siblingsIds;
    // Find child's parents
    for ( const auto& parent_ptr : child->parents_)
    {
        // If the child has parents
        if ( parent_ptr != nullptr)

        // Find all the children of the parent
        for ( const auto& sibling_ptr : parent_ptr->children_)
        {
            // Exclude the child of entry for output
            if ( sibling_ptr->id_ != child_id)
            {
                siblingsIds.insert(sibling_ptr->id_);
            }
        }
    }
    printGroup(child_id, "siblings", siblingsIds, output);
}


// Prints cousins of input person
void Familytree::printCousins(Params params,
                              std::ostream &output) const
{
    StrRef child_id = params.at(0);
    Person* child = getPointer(child_id);

    // Check if the person exists, then print
    if ( child == nullptr )
    {
        printNotFound(child_id, output);
        return;
    }

    IdSet cousinsIds;
    // Find person's parents
    for ( const auto& parent_ptr : child->parents_)
    {
        // If the person has any parents
        if ( parent_ptr != nullptr)
        {
            for ( const auto& grandparent_ptr : parent_ptr->parents_)
            {
                if ( grandparent_ptr != nullptr )
                {
                    for ( const auto& parentsibling_ptr : grandparent_ptr->children_)
                    {
                        if ( parentsibling_ptr != nullptr &&
                             parentsibling_ptr->id_ != parent_ptr->id_)
                        {
                            for ( const auto& cousin_ptr : parentsibling_ptr->children_)
                            {
                                if ( cousin_ptr != nullptr)
                                {
                                    cousinsIds.insert(cousin_ptr->id_);
                                }
                            }
                        }
                     }
                }
            }
        }
    }

    printGroup(child_id, "cousins", cousinsIds, output);
}


// Refer helper functions findpeakInLineage for the logic function

// Print tallest person in input person's lineage
void Familytree::printTallestInLineage(Params params,
                                       std::ostream &output) const
{
    StrRef id = params.at(0);
    Person* tallestPerson = findPeakInLineage(id, true);  // true for tallest
    printLineage(id, "tallest", tallestPerson, output);
}

// Prints shortest person in input person's lineage
void Familytree::printShortestInLineage(Params params,
                                        std::ostream &output) const
{
    StrRef id = params.at(0);
    Person* shortestPerson = findPeakInLineage(id, false);  // false for shortest
    printLineage(id, "shortest", shortestPerson, output);
}


// Prints grandchildren of input person at a specified generational level
void Familytree::printGrandChildrenN(Params params,
                                     std::ostream &output) const
{
    StrRef parent_id = params.at(0);
    Person* parent = getPointer(parent_id);

    // Check if the person exists,
    if ( parent == nullptr )
    {
        printNotFound(parent_id, output);
        return;
    }

    // Get the generation level
    int levels = std::stoi(params.at(1));
    if ( levels < 1 )
    {
        output << WRONG_LEVEL << std::endl;
        return;
    }

    IdSet grandchildren;

    findGenerationAtLevel(parent, grandchildren, levels, true);
    printLinealRelation(parent_id, "grandchildren", levels, grandchildren, output);
}


// Prints grandparents of input person at a specified generational level
void Familytree::printGrandParentsN(Params params,
                                    std::ostream &output) const
{
    StrRef child_id = params.at(0);
    Person* child = getPointer(child_id);

    // Check if the person exists,
    if ( child == nullptr )
    {
        printNotFound(child_id, output);
        return;
    }

    // Get the generation level
    int levels = std::stoi(params.at(1));
    if ( levels < 1 )
    {
        output << WRONG_LEVEL << std::endl;
        return;
    }

    IdSet grandparents;

    findGenerationAtLevel(child, grandparents, levels, false);
    printLinealRelation(child_id, "grandparents", levels, grandparents, output);
}


// Helper Functions

// Retrieves a pointer to a Person
Person *Familytree::getPointer(const std::string &id) const
{
    // To find the person by id in the data_map
    auto iter = data_.find(id);
    if (iter != data_.end())
    {
        // if exixts, return the pointer to the Person object
        return iter->second.get();
    }

    return nullptr;
}


// Prints an error message if a person does not exist
void Familytree::printNotFound(const std::string &id,
                               std::ostream &output) const
{
     output << "Error. " << id << " not found." << std::endl;
}


// Converts a vector;Person* to a set of person IDs
IdSet Familytree::vectorToIdSet(const std::vector<Person *>
                                &container) const
{
    // Initializing by creating an empty IdSet
    IdSet idset;

    for ( const Person* person : container )
    {
        if ( person != nullptr ) // Ensure the pointer is not null
        {
            idset.insert(person->id_); // insert the person's ID into the set
        }
    }

    return idset; // return the set of IDs
}


// Prints input person's relations w.r.t IdSet
void Familytree::printGroup(const std::string &id,
                            const std::string &group,
                            const IdSet &container,
                            std::ostream &output) const
{
    // Check if the group is empty
    size_t groupSize = container.size();
    if (groupSize == 0)
    {
        output << id << " has no " << group << "." << std::endl;
        return;
    }
    // Print the group size with count
     output << id << " has " << groupSize << " " << group << ":" << std::endl;

    // Print each ID in the container
    for (const auto& memberId : container)
    {
        // Print each member ID on a new line
        output << memberId << std::endl;
    }
}


// Recursive function to collect all descendants of input person
void Familytree::getDescendants(const std::string &id,
                                IdSet&descendants) const
{
    Person* person = getPointer(id);

    // Check if the person exists
    if ( person == nullptr)
    {
        return;
    }
    // To add the person to the descendants set
    descendants.insert(id);

    // To get descendants recursively for each child
    for ( const auto& child : person->children_)
    {
        getDescendants(child->id_, descendants);
    }
}


// Compares peak height (max/min) of input person's lineage
Person* Familytree::findPeakInLineage(const std::string &id,
                                      bool findTallest) const
{
    Person* peakPerson = getPointer(id);

    if (peakPerson == nullptr)
    {
        return nullptr;
    }

    // Collect all descendants of the person
    IdSet descendants;
    getDescendants(id, descendants);

    int peakHeight = peakPerson->height_;

    // Iterate through the descendants
    for (const auto& descendant_id : descendants)
    {
        Person* descendant_ptr = getPointer(descendant_id);
        if (descendant_ptr)
        {
            if (findTallest)
            {
                // Finding the tallest - if true
                if (descendant_ptr->height_ > peakHeight)
                {
                    peakPerson = descendant_ptr;
                    peakHeight = descendant_ptr->height_;
                }
            }
            else
            {
                // Finding the shortest- if false
                if (descendant_ptr->height_ < peakHeight)
                {
                    peakPerson = descendant_ptr;
                    peakHeight = descendant_ptr->height_;
                }
            }
        }
    }

    return peakPerson;
}


// Prints the result of input person's peak lineage
void Familytree::printLineage(const std::string &id,
                                    const std::string &type,
                                    Person* peakPerson,
                                    std::ostream &output) const
{
    if (peakPerson == nullptr)
    {
        printNotFound(id, output);
        return;
    }

    int peakHeight = peakPerson->height_;
    if (peakPerson->id_ == id)
    {
        output << "With the height of " << peakHeight << ", "
               << peakPerson->id_ << " is the " << type
               << " person in his/her lineage." << std::endl;
    }
    else
    {
        output << "With the height of " << peakHeight << ", "
               << peakPerson->id_ << " is the " << type
               << " person in " << id << "'s lineage." << std::endl;
    }
}


// Retrieves children of input person
void Familytree::findChildren(Person *parent,
                              IdSet &descendants) const
{
    for(const auto& children_ptr: parent->children_)
    {
        if(children_ptr!=nullptr)
        {
            descendants.insert(children_ptr->id_);
        }
    }
}


// Retrieves parents of input person
void Familytree::findParent(Person *child,
                            IdSet &ancestors) const
{
    for ( const auto& parent_ptr : child->parents_)
    {
        if ( parent_ptr != nullptr )
        {
            ancestors.insert(parent_ptr->id_);
        }
    }
}


// Finds generational set of input person at a level
void Familytree::findGenerationAtLevel(Person *person, IdSet &generationalIds,
                                       int levels, bool findlinealrelation) const
{
    IdSet current_generation;
    {
        // Find immdediate lineal generation
        if(findlinealrelation)
        {
            // Find children if true
            findChildren(person, current_generation);
        }
        else
        {
            // Find parents if false
            findParent(person, current_generation);
        }

        IdSet next_generation;
        for ( int i = 0; i < levels; ++i) // To find the required generational level
        {
            next_generation.clear();
            for ( const auto& id : current_generation)
            {
                Person* linealrelative_ptr = getPointer(id);
                if ( linealrelative_ptr != nullptr )
                {
                    if (findlinealrelation)
                    {
                        findChildren(linealrelative_ptr, next_generation);
                    }
                    else
                    {
                        findParent(linealrelative_ptr, next_generation);
                    }
                }
            }

            // Update current to next generation
            current_generation = next_generation;
        }

        // Store it in the set
        generationalIds = current_generation;
    }
}


// Prints lineal relationships of input person at a level
void Familytree::printLinealRelation(const std::string &id,
                                     const std::string &linealrelation,
                                     int levels, const IdSet &generationalIds,
                                     std::ostream &output) const
{
    std::string all = "";

    // For the prefix output
    for ( int i = 0; i < levels - 1; ++i)
    {
        all = all + n;
    }

    if (generationalIds.empty())
    {
        output << id << " has no " << all << linealrelation << "."
               << std::endl;
    }
    else
    {
        output << id << " has " << generationalIds.size() << " "
               << all << linealrelation << ":" << std::endl;
        for ( const auto& member : generationalIds)
        {
            output << member << std::endl;
        }
    }
}
