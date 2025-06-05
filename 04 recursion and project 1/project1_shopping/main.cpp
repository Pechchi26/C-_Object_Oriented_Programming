/* Chain stores
 *
 * Desc:
 *   This program reads input data concerning chain stores from an input
 * file, the lines of which are of the form:
 * chain_store;store_location;product_name;product_price.
 * The program checks if each line consists of the abovementioned four
 * data fields.
 *   The data written in the file is collected into an appropriate data
 * structure consisting of STL containers and structs. After that the user
 * can make searches for the data structure by using the commands
 * chains, stores, selection, cheapest, and products. These commands
 * have a varying number of parameters, and the program checks if the
 * user gave a correct number of parameters and if the given parameters
 * (chain store, store location, product name) can be found from the data
 * structure.
 *   The program terminates with the command quit.
 *
 * Program author ( Fill with your own info )
 * Name: Rong Guo, Pechchuma Manoharan
 * Student number: 152688192, 153064090
 * UserID: mcc996, mpp349 ( Necessary due to gitlab folder naming )
 * E-Mail: rong.guo@tuni.fi, pechchuma.manoharan@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 * Functions for all four fields
 * Main function for user interface
 * Utility function for repetition
 *
 *
 * */

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <set>
#include <functional>


using namespace std;

//Make a struct with product its price
struct Product
{
    string product_name;
    string product_price ;
    Product(const string& n = "", const string& p = "") : //initialize the product
       product_name(n), product_price(p) {}
};



//Read the file data into map
void read_file_into_map(ifstream& file, map<string, map<string,
                        map<string,Product>>>& shopmap)
{
    string line;
    string chain_store="";
    string store_location="";
    string product_name="";
    string product_price="";
    while(getline(file,line))
    {
        //Spilit the lines into four fields
        size_t pos =line.find(";");
        chain_store = line.substr(0, pos);
        line = line.substr(pos+1);
        pos =line.find(";");
        store_location = line.substr(0, pos);
        line = line.substr(pos+1);
        pos =line.find(";");
        product_name = line.substr(0, pos);
        product_price = line.substr(pos+1);

        //Insert four fields into map
        shopmap[chain_store][store_location][product_name]=
                Product(product_name,product_price);

        if (chain_store.empty() || store_location.empty()
                || product_name.empty() || product_price.empty())
              {
                  cout << "Error: the input file has an erroneous line "<< endl;
                  exit (EXIT_FAILURE);
              }
    }
}



//Utility function for error message
void print_command_error(const string& command)
{
    cout << "Error: error in command " << command << endl;
}



//Print all the chains in the file
void command_chains(const string& command,
                    map<string, map<string, map<string,Product>>>& shopmap)
{
    if (command=="chains")
    {
        for (const auto& chain : shopmap)
        {
            cout << chain.first<< endl;
        }
    }
    else
    {
        print_command_error("chains");
    }
}



//Print all the stores of the chain
void command_chains_store(const string& command_store,
                          map<string, map<string, map<string,Product>>>& shopmap)
{
    //Split the command
    string chain = command_store.substr(0, command_store.find(" "));
    string chain_name =command_store.substr(command_store.find(" ")+1);

    if(command_store.find(" ")==string::npos || chain_name.find(" ")!=string::npos)
    {
        print_command_error("stores");
        return;
    }


    if(chain=="stores")
    {
        //Find the chain_name user input and print all the stores of the chain
        if (shopmap.find(chain_name)!=shopmap.end())
        {
            map<string, map<string,Product>>& stores=shopmap[chain_name];
            for(const auto& store : stores)
            {
                cout<<store.first<<endl;
            }
        }
        else
        {
            cout<<"Error: unknown chain name"<<endl;
        }
     }
    else
    {
        print_command_error("stores");
    }
}



//Print all the products and prices of the selected store
void command_selection(const string& command,
                       map<string, map<string, map<string,Product>>>& shopmap)
{
    //Split the command into selection, chain and store
    string selection = command.substr(0, command.find(" "));
    string line = command.substr(command.find(" ")+1);
    string chain = line.substr(0,line.find(" "));
    string store =line.substr(line.find(" ")+1);

    if(command.find(" ")==string::npos || line.find(" ")==string::npos || store.find(" ")!=string::npos)
    {
        print_command_error("selection");
        return;
    }

    if (shopmap.find(chain)!=shopmap.end())
    {
        const map<string,map<string, Product>>& stores=shopmap.find(chain)->second;
        if(stores.find(store)!=stores.end())
        {
            const map<string, Product>& products = stores.find(store)->second;
            for (const auto& product : products)
            {
               if(product.second.product_price=="out-of-stock")
               {
                   cout<< product.first<<" out of stock"<< endl;
               }
               else
               {
                   cout<<product.first<<" "<<product.second.product_price<<endl;
               }
            }
        }
        else
        {
            cout<<"Error: unknown store"<<endl;
        }
    }
    else
    {
        cout<<"Error: unknown chain name"<<endl;
        return;
    }
}



//Print the cheapest price, chain and store of the required product
void command_cheapest(const string& cheapest,
                      map<string, map<string, map<string,Product>>>& shopmap)
{
    //Split the cheapest command into command and product
    string command = cheapest.substr(0, cheapest.find(" "));
    string product =cheapest.substr(cheapest.find(" ")+1);

    if(cheapest.find(" ")==string::npos || product.find(" ")!=string::npos)
    {
        print_command_error("cheapest");
        return;
    }

    string cheapest_chain="";
    string cheapest_store="";
    double cheapest_price = numeric_limits<double>::max();
    bool product_found=false;
    bool out_of_stock=true;
    vector<pair<string,string>>cheapest_stores;

    for(const auto& chain :shopmap)
    {
        for(const auto& store: chain.second)
        {
            for(const auto& products: store.second)
            {
                if(products.first==product)
                {
                    product_found=true;
                    if(products.second.product_price!="out-of-stock")
                    {
                        out_of_stock = false;
                        double price=stod(products.second.product_price);
                        if(price<=cheapest_price)
                        {
                            cheapest_price = price;
                            cheapest_stores.push_back(make_pair(chain.first, store.first));
                        }
                    }
                }
            }
        }
    }
        if(not product_found)
        {
            cout<<"The product is not part of product selection"<<endl;
            return;
        }
        if(out_of_stock)
        {
            cout<<"The product is temporarily out of stock everywhere"<<endl;
            return;
        }

        cout<< fixed << setprecision(2);
        cout<<cheapest_price<<" euros"<<endl;
        for(const auto& store_ifo :cheapest_stores)
        {
             cout<< store_ifo.first<<" "<<store_ifo.second<<endl;
        }
}



//Print all the products in the flie
void products(const string& command, map<string,
              map<string, map<string,Product>>>& shopmap)
{
    if(command=="products")
    {
        map<string,bool> not_same_product;
        for(const auto& chain :shopmap)
        {
            for(const auto& store: chain.second)
            {
                for(const auto& products: store.second)
                {
                    not_same_product[products.second.product_name]=true;
                }
            }
        }
        for (const auto& product : not_same_product)
        {
            cout << product.first << endl;
        }
    }
    else
    {
        print_command_error("products");
    }
}



//Main function - To execute the program
int main()
{
    using MapType =map<string, map<string,map<string,Product>>>;
    MapType shopping;
    string input_file_name = "";
    cout << "Input file: ";
    getline(cin,input_file_name);

    //Open the input file
    ifstream input_file_object(input_file_name);

    //Check if the input file is wrong
    if(not input_file_object)
    {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    read_file_into_map(input_file_object,shopping);
    input_file_object.close(); //finish read

    //Implement map commands
    map<string, function<void(const string&, MapType&)>> command_map =
    {
        {"chains", command_chains},
        {"stores", command_chains_store},
        {"selection", command_selection},
        {"cheapest", command_cheapest},
        {"products", products},
    };

    //To execute command
    while(true)
    {
        cout <<"> " ;
        string command="";
        getline(cin,command);
        string command_one_word=command.substr(0,command.find(" "));

        if(command_one_word=="quit")
        {
            return EXIT_SUCCESS;
        }

        //Check for the command in the map
        auto it = command_map.find(command_one_word);
        if (it != command_map.end())
        {
            it->second(command, shopping);
        }
        else
        {
            cout << "Error: unknown command: " << command << endl;
        }
    }
    return 0;
}
