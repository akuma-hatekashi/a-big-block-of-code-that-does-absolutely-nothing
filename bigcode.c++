//Program tested on Microsoft Visual Studio 2010 - Zahid Ghadialy
//Example demonstrates creating an XML file 
//Based on example at: http://www.codeproject.com/Articles/32762/Xerces-for-C-Using-Visual-C-Part-2
//Xerces is xerces-c-3.1.1-x86-windows-vc-10.0

 
#include <iostream>
#include <string>
#include <sstream>
//Mandatory for using any feature of Xerces.
#include <xercesc/util/PlatformUtils.hpp>
//Use the Document Object Model (DOM) API
#include <xercesc/dom/DOM.hpp>
//Required for outputing a Xerces DOMDocument to a standard output stream (Also see: XMLFormatTarget)
#include <xercesc/framework/StdOutFormatTarget.hpp>
//Required for outputing a Xerces DOMDocument to the file system (Also see: XMLFormatTarget)
#include <xercesc/framework/LocalFileFormatTarget.hpp>

 
 
using namespace std;
XERCES_CPP_NAMESPACE_USE
 
void DoOutput2Stream(DOMDocument* pmyDOMDocument);
void DoOutput2File(DOMDocument* pmyDOMDocument, const wchar_t * FullFilePath );
 
int main()
{
  // Initilize Xerces.
  XMLPlatformUtils::Initialize();
 
  // Pointer to our DOMImplementation.
  DOMImplementation*    p_DOMImplementation = NULL;
  p_DOMImplementation = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("core"));
 
  // Pointer to our DOMDocument.
  DOMDocument*        p_DOMDocument = NULL;
 
  p_DOMDocument = p_DOMImplementation->createDocument(0, L"Hello_World", 0);
 
  DOMElement * p_RootElement = NULL;
  p_RootElement = p_DOMDocument->getDocumentElement();
 
  //Fill in the DOM document - different parts
  //Create a Comment node, and then append this to the root element.
  DOMComment * p_DOMComment = NULL;
  p_DOMComment = p_DOMDocument->createComment(L"Dates are formatted mm/dd/yy." 
                                            L" Don't forget XML is case-sensitive.");
  p_RootElement->appendChild(p_DOMComment);
 
  //Create an Element node, then fill in some attributes, and then append this to the root element.
  DOMElement * p_DataElement = NULL;
  p_DataElement = p_DOMDocument->createElement(L"data");
 
  //Copy the current system date to a buffer, then set/create the attribute.
  wchar_t wcharBuffer[128];
  _wstrdate_s(wcharBuffer, 9);
  p_DataElement->setAttribute(L"date", wcharBuffer);
 
  //Convert an integer to a string, then set/create the attribute.
  _itow_s(65536, wcharBuffer, 128, 10);
  p_DataElement->setAttribute(L"integer", wcharBuffer);
 
  //Convert a floating-point number to a wstring, then set/create the attribute.
  std::wstringstream    myStream;
  myStream.precision(8);
  myStream.setf(std::ios_base::fixed, std::ios_base::floatfield);
  myStream << 3.1415926535897932384626433832795;
  const std::wstring ws(myStream.str());
  p_DataElement->setAttribute(L"float", ws.c_str());
  p_RootElement->appendChild(p_DataElement);
 
  // Create an Element node, then fill in some attributes, add some text,
  // then append this to the 'pDataElement' element.
  DOMElement * p_Row = NULL;
  p_Row = p_DOMDocument->createElement(L"row");
 
  // Create some sample data.
  _itow_s(1, wcharBuffer, 128, 10);
  p_Row->setAttribute(L"index", wcharBuffer);
 
  /*
  Create a text node and append this as well. Some people 
  prefer to place their data in the text node
  which is perfectly valid, others prefer to use 
  the attributes. A combination of the two is quite common.
  */
  DOMText* p_TextNode = NULL;
  p_TextNode = p_DOMDocument->createTextNode(L"Comments and" 
              L" data can also go in text nodes.");
  p_Row->appendChild(p_TextNode);
 
  p_DataElement->appendChild(p_Row);
 
 
  // Create another row (this time putting data and descriptions into different places).
  p_Row = p_DOMDocument->createElement(L"row");
  p_Row->setAttribute(L"description", L"The value of PI");
  p_TextNode = p_DOMDocument->createTextNode(L"3.1415926535897932384626433832795");
  p_Row->appendChild(p_TextNode);
  p_DataElement->appendChild(p_Row);
 
  // Create another row.
  p_Row = p_DOMDocument->createElement(L"row");
  p_Row->setAttribute(L"website", L"http://www.3g4g.co.uk/");
  p_TextNode = p_DOMDocument->createTextNode(L"3G and 4G Wireless Resources");
  p_Row->appendChild(p_TextNode);
  p_DataElement->appendChild(p_Row);
 
  //Output on console
  DoOutput2Stream(p_DOMDocument);
 
  //Output to a file
  DoOutput2File(p_DOMDocument, XMLString::transcode("..\\..\\XML\\Test.xml"));
 
  // Cleanup.
  p_DOMDocument->release();
  XMLPlatformUtils::Terminate();
 
  return 0;
}
 
 
void DoOutput2Stream(DOMDocument* pmyDOMDocument)
{
  DOMImplementation    *pImplement    = NULL;
  DOMLSSerializer      *pSerializer   = NULL;
  XMLFormatTarget      *pTarget       = NULL;
 
  /*
  Return the first registered implementation that has
  the desired features. In this case, we are after
  a DOM implementation that has the LS feature... or Load/Save.
  */
  pImplement = DOMImplementationRegistry::getDOMImplementation(L"LS");
 
  /*
  From the DOMImplementation, create a DOMWriter.
  DOMWriters are used to serialize a DOM tree [back] into an XML document.
  */
  pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
 
  /*
  This line is optional. It just sets a feature
  of the Serializer to make the output
  more human-readable by inserting line-feeds and tabs, 
  without actually inserting any new nodes
  into the DOM tree. (There are many different features to set.) 
  Comment it out and see the difference.
  */
 
  //The end-of-line sequence of characters to be used in the XML being written out. 
  pSerializer->setNewLine(XMLString::transcode("\n"));
 
  DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
  pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
 
 
  /*
  Choose a location for the serialized output. The 3 options are:
      1) StdOutFormatTarget     (std output stream -  good for debugging)
      2) MemBufFormatTarget     (to Memory)
      3) LocalFileFormatTarget  (save to file)
      (Note: You'll need a different header file for each one)
  */
  pTarget = new StdOutFormatTarget();
  DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
  pDomLsOutput->setByteStream(pTarget);
  
  // Write the serialized output to the target.
  pSerializer->write(pmyDOMDocument, pDomLsOutput);
}
 
void DoOutput2File(DOMDocument* pmyDOMDocument, const wchar_t * FullFilePath )
{
 
  DOMImplementation    *pImplement     = NULL;
  DOMLSSerializer      *pSerializer    = NULL;
  XMLFormatTarget      *pTarget        = NULL;
 
  /*
  Return the first registered implementation that 
  has the desired features. In this case, we are after
  a DOM implementation that has the LS feature... or Load/Save.
  */
  pImplement = DOMImplementationRegistry::getDOMImplementation(L"LS");
 
  /*
  From the DOMImplementation, create a DOMWriter.
  DOMWriters are used to serialize a DOM tree [back] into an XML document.
  */
  pSerializer = ((DOMImplementationLS*)pImplement)->createLSSerializer();
 
 
  /*
  This line is optional. It just sets a feature 
  of the Serializer to make the output
  more human-readable by inserting line-feeds, 
  without actually inserting any new elements/nodes
  into the DOM tree. (There are many different features to set.) 
  Comment it out and see the difference.
  */
  DOMConfiguration* pDomConfiguration = pSerializer->getDomConfig();
  pDomConfiguration->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
 
 
  /*
  Choose a location for the serialized output. The 3 options are:
      1) StdOutFormatTarget     (std output stream -  good for debugging)
      2) MemBufFormatTarget     (to Memory)
      3) LocalFileFormatTarget  (save to file)
      (Note: You'll need a different header file for each one)
      Don't forget to escape file-paths with a backslash character, or
      just specify a file to be saved in the exe directory.
        
        eg. c:\\example\\subfolder\\pfile.xml
 
  */
  pTarget = new LocalFileFormatTarget(FullFilePath);
  // Write the serialized output to the target.
  DOMLSOutput* pDomLsOutput = ((DOMImplementationLS*)pImplement)->createLSOutput();
  pDomLsOutput->setByteStream(pTarget);
 
  pSerializer->write(pmyDOMDocument, pDomLsOutput);
}
//Program tested on Microsoft Visual Studio 2010 - Zahid Ghadialy
//Example demonstrates reading an XML file and printing it out

 
#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include "DomReader.h"

using namespace std;
 
 
int main()
{
  string xmlFileName="..\\..\\XML\\books.xml";
  
  DomReader myDomReader;
 
  try
  {
    myDomReader.readDomFile(xmlFileName);
  }
  catch (runtime_error e)
  {
    cout << e.what() <<endl;
  }
  catch(...)
  {
    cout << "Unexpected error occurred" << endl;
  }
 
  return 0;
}
#include <string>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

using namespace std;
XERCES_CPP_NAMESPACE_USE
 
class DomReader
{
public:
  DomReader();
  ~DomReader();
 
  void readDomFile(std::string&) throw(std::runtime_error);
  
 
private:
  void convertDomToXmlString(DOMNode* domNode, std::string &) throw(std::runtime_error);
  string narrow( const wstring& str );
  xercesc::XercesDOMParser *domFileParser;
 
};
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
 
#include "DomReader.h"

 
DomReader::DomReader()
{
  XMLPlatformUtils::Initialize();
  domFileParser = new XercesDOMParser;
  domFileParser->setValidationScheme(XercesDOMParser::Val_Never);
  domFileParser->setDoNamespaces(false);    // optional
}
 
DomReader::~DomReader()
{
  if(domFileParser)
    delete domFileParser;
  XMLPlatformUtils::Terminate();
}
 
void DomReader::readDomFile(string& domFileName) throw(std::runtime_error)
{
  //Check if filename / file is good
  struct _stat fileStatus;
 
  int returnStat = _stat(domFileName.c_str(), &fileStatus);
  if ( returnStat == ENOENT )
    throw ( runtime_error("Path file_name does not exist, or path is an empty string.") );
  else if ( returnStat == ENOTDIR )
    throw ( std::runtime_error("A component of the path is not a directory."));
  else if( returnStat == ELOOP )
    throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
  else if( returnStat == EACCES )
    throw ( std::runtime_error("Permission denied."));
  else if( returnStat == ENAMETOOLONG )
    throw ( std::runtime_error("File can not be read\n"));
  else if( returnStat == -1)
    throw ( std::runtime_error("Other Unknown Error\n"));
 
  //Parse the file
  domFileParser->parse(domFileName.c_str());
 
  //No need to free this pointer - owned by the parent parser object
  DOMDocument* xmlDoc = domFileParser->getDocument();
  if( !xmlDoc ) throw(std::runtime_error( "DOM document could not be opened" ));
 
  //Get the top-level element: Name is "root". No attributes for "root"
  DOMElement* elementRoot = xmlDoc->getDocumentElement();
  if( !elementRoot ) throw(std::runtime_error( "empty XML document" ));
 
  string xmlString;
  try
  {
    convertDomToXmlString(elementRoot, xmlString);
  }
  catch(runtime_error e)
  {
    throw(runtime_error(e));
  }
  cout << "DOM File: "<< domFileName << " output is as follows "<<endl;
  cout << xmlString;
  cout << endl;
}
 
void DomReader::convertDomToXmlString(DOMNode* domNode, string &xmlString) throw(std::runtime_error)
{
  try
  {
    DOMImplementation *domImpl = DOMImplementationRegistry::getDOMImplementation(L"LS");
    DOMLSSerializer   *domSerializer = ((DOMImplementationLS*)domImpl)->createLSSerializer();
    XMLCh *xmlBuffer = domSerializer->writeToString(domNode);
    xmlString = narrow(xmlBuffer);
    XMLString::release (&xmlBuffer);
    delete domSerializer;
  }
  catch(XMLException& e)
  {
    char *xmlErrMessage = XMLString::transcode(e.getMessage());
    throw runtime_error(xmlErrMessage);
  }
  catch(...)
  {
    throw runtime_error("Unknown error in convertDomToXmlString\n");
  }
}
 
string DomReader::narrow( const wstring& str )
{
  ostringstream stm ;    
  const ctype<char>& ctfacet = use_facet< ctype<char> >( stm.getloc() ) ;    
  for( size_t i=0 ; i<str.size() ; ++i )
    stm << ctfacet.narrow( str[i], 0 ) ;    
  return stm.str() ;
}
//Program tested on Microsoft Visual Studio 2008 - Zahid Ghadialy
//Simple example of multiset

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Product //Keeping this simple
{
public:
Product(string name, int code, int price) :
  name_(name), productCode_(code), price_(price)
  {
    quantity_ = 10; //Lets fix this value for simplicity
    }
bool availableForSale()
{
  if(quantity_ > 0)
  {
    quantity_--;
    return true;
  }
  return false;
}
string name_;
int productCode_;
int price_;
int quantity_;
private:
Product(); //Disabled the default constructor
};

void sellProduct(string name, multimap<string, Product*>& inventory, multiset <int> &soldItems)
{
multimap<string, Product*>::iterator it = inventory.find(name);
if(it != inventory.end())
{
  if ((*it->second).availableForSale())
  {
    soldItems.insert((*it->second).productCode_);
  }
}
else
{
  cout << "Unknown product : " << name << endl;
}
}

void soldItemsList(multimap<string, Product*>& inventory, multiset <int> &soldItems)
{
multimap<string, Product*>::iterator it = inventory.begin();
for(it = inventory.begin(); it != inventory.end(); ++it)
{
  int soldCount = soldItems.count((*it->second).productCode_);
  cout<<"Product = " << (*it->second).name_ << ", Quantity Sold = " << soldCount << endl;
}
}

int checkSales(multimap<string, Product*>& inventory, multiset <int> &soldItems)
{
int totalSales = 0;
multimap<string, Product*>::iterator it;
for(it = inventory.begin(); it != inventory.end(); ++it)
{
  int soldCount = soldItems.count((*it->second).productCode_);
  totalSales += soldCount * (*it->second).price_;
}
return totalSales;
}

int main()
{
//There is no special reason to use multimap instead of a map
//If you wanted to add same product and create quantity multimap is required
  multimap<string, Product*> inventory;
Product* prod1 = new Product("product1", 2334, 10);
Product* prod2 = new Product("product2", 4556, 50);
inventory.insert(pair<string, Product*>("product1",prod1));
inventory.insert(pair<string, Product*>("product2",prod2));

multiset <int> soldItems;

sellProduct("product1", inventory, soldItems);
sellProduct("product2", inventory, soldItems);
sellProduct("apple", inventory, soldItems);
sellProduct("product1", inventory, soldItems);
sellProduct("product1", inventory, soldItems);
sellProduct("product2", inventory, soldItems);

soldItemsList(inventory, soldItems);

cout<<"Total sales = " << checkSales(inventory, soldItems) << endl;

delete prod1;
delete prod2;
return 0;
}
//Program tested on Microsoft Visual Studio 2008 - Zahid Ghadialy
//Simple example of multiset

#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
 int a[ 10 ] = { 7, 22, 9, 1, 18, 30, 100, 22, 85, 13 };
 int aSize = sizeof(a) / sizeof(int);
 std::multiset< int, std::less< int > > intMultiset(a, a + aSize);

 cout << "Printing out all the values in the multiset : ";
 multiset<int>::iterator it;
 for ( it = intMultiset.begin(); it != intMultiset.end(); ++it)
   cout << "  " << *it;
 cout << endl << endl;

 std::ostream_iterator< int > output( cout, " " );

 cout << "There are currently " << intMultiset.count( 15 )
      << " values of 15 in the multiset\n\n";

 intMultiset.insert( 15 );
 intMultiset.insert( 15 );

 cout << "After two inserts, there are currently " << intMultiset.count( 15 )
      << " values of 15 in the multiset\n\n";

 cout << "Printing out all the values in the multiset : ";
 for ( it = intMultiset.begin(); it != intMultiset.end(); ++it)
   cout << "  " << *it;
 cout << endl << endl;

 return 0;
}
//Program tested on Microsoft Visual Studio 2008 - Zahid Ghadialy
#include<iostream>

using namespace std;

int main()
{
 int i = 123;
 auto int j = 456;
 register int k = 789;

 cout<<"Address of i = " << &i <<", Value = " << i << endl;
 cout<<"Address of j = " << &j <<", Value = " << j << endl;
 cout<<"Address of k = " << &k <<", Value = " << k << endl;

 return 0;
}
