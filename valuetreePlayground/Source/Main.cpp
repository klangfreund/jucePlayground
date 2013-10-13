#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>
using namespace std;

//==============================================================================
int main (int argc, char* argv[])
{
    cout << endl;
    cout << "Following the introduction at"
            "rawmaterialsoftware.com/wiki/index.php/Basic_ValueTree_Usage"
         << endl << endl;
    cout << "**********************" << endl;
    cout << "Basic value tree usage" << endl;
    cout << "**********************" << endl;

    cout << endl;
    cout << "An invalid ValueTree" << endl;
    cout << "--------------------" << endl;

    ValueTree myInvalidNode; // Create an empty, invalid ValueTree
    
    //if (!myNode.isValid())    is equal to
    if (myInvalidNode == ValueTree::invalid)
    {
        cout << "myInvalidNode is invalid." << endl;
    }

    cout << endl;
    cout << "A valid ValueTrees" << endl;
    cout << "------------------" << endl;

    // A valid node has a type
    Identifier myNodeType ("myNodeType"); // Create an Identifier.
    ValueTree myNode (myNodeType); // This is a valid node, of type “MyNode”.

    myNode.isValid() ? cout << "myNode is valid" << endl 
                     : cout << "myNode is invalid" << endl;

    cout << "myNode.getType() = " + String(myNode.getType()) << endl;

    cout << endl;
    cout << "Sharing valid ValueTrees" << endl;
    cout << "------------------------" << endl;

    // Initializing with the copy constructor.
    ValueTree sameNode (myNode); // This object points to the same data as myNode

    // Create an empty node and assign the content of another node later.
    cout << "Creat an otherNode" << endl;
    ValueTree otherNode (myNodeType); // This creates an empty ValueTree with type “MyNodeType”...
    if (otherNode.getNumProperties() == 0 && otherNode.getNumChildren() == 0)
    {
        cout << "otherNode is empty (no properties and no children)" << endl;
    }
    otherNode = sameNode; // ... but the object now points to the first instance


    cout << endl;
    cout << "*********************" << endl;
    cout << "Basic property access" << endl;
    cout << "*********************" << endl;

    UndoManager* undoManager = nullptr; // Needed for the ValueTree::setProperty(...)


    cout << endl;
    cout << "Setting a property" << endl;
    cout << "------------------" << endl;

    // You must provide an Identifier to specify the name of the property you 
    // wish to set, and a var value for it to take.
    Identifier propertyName ("name");
    myNode.setProperty (propertyName, "Fluffmuff", undoManager);


    cout << endl;
    cout << "Getting a property" << endl;
    cout << "------------------" << endl;

    //var nameVar = myNode.getProperty (propertyName);
    // or
    var nameVar = myNode [propertyName];
    String name = myNode [propertyName]; // This typecast works.
//    String name2 (myNode [propertyName]); // This String construction does
                                          // not work.
//TODO: Ask why! It works with a var holding a double!! See some lines below.
//      Or figure it out yourself.
//      myNode [propertyName] returns a var.
//      There is var::operator String () const.
    
    cout << "name = " + name.toStdString() << endl;


    cout << endl;
    cout << "Setting a double property" << endl;
    cout << "-------------------------" << endl;

    Identifier propertySize ("size");
    myNode.setProperty (propertySize, 2.4, nullptr);
    double size = myNode [propertySize]; // This typecast works.
    double size2 = double (myNode[propertySize]); // Constructing a double from
                                                  // a var DOES work.
    cout << "size = " << size << endl;


    cout << endl;
    cout << "Finding out about properties" << endl;
    cout << "----------------------------" << endl;

    int numberOfProperties = myNode.getNumProperties ();
    cout << "numberOfProperties = " << numberOfProperties << endl;
    
    cout << endl;
    cout << "Property names:" << endl;
    for (int i=0; i < numberOfProperties; ++i)
    {
        Identifier aGivenPropertyName (myNode.getPropertyName (i));
        cout << String(aGivenPropertyName) << endl;
    }

    cout << endl;
    if (myNode.hasProperty (Identifier("size")))
    {
        cout << "myNode has a property called \"size\"." << endl;
    }
    if (!myNode.hasProperty (Identifier("length")))
    {
        cout << "myNode does not have a property called \"length\"." << endl;
    }

    
    cout << endl;
    cout << "Basic child access" << endl;
    cout << "==================" << endl;

    cout << endl;
    cout << "Adding a child" << endl;
    cout << "--------------" << endl;

    Identifier childNodeType ("childNodeType"); // Create an Identifier
    ValueTree childNode (childNodeType);
    // Identifier propertyName ("name");
    myNode.addChild (childNode, -1, undoManager);
        // Parameter: -1 : Add it to the end of the list.
    
    cout << endl;
    cout << "Getting a child" << endl;
    cout << "---------------" << endl;

    cout << "myNode.getNumProperties() = " << myNode.getNumProperties() << endl;
        // ... = 2
    cout << "myNode.getNumChildren() = " << myNode.getNumChildren() << endl;
        // ... = 1
    // -> A ValueTree has different counters for properties and for children!

    cout << "Getting a child by index:" << endl;
    childNode = myNode.getChild (0);
    if (childNode.isValid())
    {
        cout << "  Found a child with index 0." << endl;
    }

    cout << "Getting a child by name:" << endl;
    childNode = myNode.getChildWithName (myNodeType);
    if (!childNode.isValid())
    {
        cout << "  Did not find a child with node type \"myNodeType\"." << endl;
    }
    childNode = myNode.getChildWithName (childNodeType);
    if (childNode.isValid())
    {
        cout << "  Found a child with node type \"childNodeType\"." << endl;
        cout << "  Add the property propertyName with the value \"nameOfChild\"" << endl;
        childNode.setProperty (propertyName, "nameOfChild", undoManager);
    }

    cout << "Looking for the first child with the property "
            "(\"propertyName\", \"nameOfChild\")...:" << endl;
    childNode = myNode.getChildWithProperty (propertyName, "nameOfChild");
    if (childNode.isValid())
    {
        cout << "... found a child." << endl;
    }
    else
    {
        cout << "... no child found." << endl;
    }
    
    cout << "childNode.getType() = " << String (childNode.getType()) << endl;

    cout << "childNode.getParent().getType() = "
         << String (childNode.getParent().getType()) << endl;

    cout << endl;
    cout << "******************************" << endl;
    cout << "Further value tree exploration" << endl;
    cout << "******************************" << endl;

    cout << endl
         << "Storing to XML" << endl
         << "==============" << endl;

    cout << "Creating an XmlElement." << endl;
    ScopedPointer<XmlElement> xml;
    xml = myNode.createXml();
    if (xml == nullptr)
    {
        cout << "Couldn't create the XML element from myNode!" << endl;
    }
    else
    {
        File destinationFile = File::getSpecialLocation (File::currentExecutableFile);
        destinationFile = destinationFile.getParentDirectory();
        destinationFile = destinationFile.getNonexistentChildFile ("myNode", ".xml");
        cout << "destinationFile.getFullPathName() = "
             << destinationFile.getFullPathName() << endl;
        
        String dtdToUse ("bla");
        xml->writeToFile (destinationFile, dtdToUse);
    }

    
    return 0;
}
