#include <iostream>
#include "cards.hh"

Cards::Cards(): top_(nullptr)
{
    std::cout << "constructor" << std::endl;
}

Cards::~Cards()
{
    std::cout << "destructor" << std::endl;
}

void Cards::add(int id)
{
    std::shared_ptr<Card_data> new_card =
            std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

bool Cards::remove(int &id)
{
    // check if the deck is empty
    if ( top_ == nullptr )
    {
        return false;
    }

    id = top_->data;
    top_= top_->next;

    return true;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    std::shared_ptr<Card_data> current = top_;
    int running_number = 1;

    while (current != nullptr)
    {
        s<<running_number<<": "<<current->data<<std::endl;
               current=current->next;
               ++running_number;
    }

}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}

bool Cards::top_to_bottom()
{
    // checking if the deck is empty
    if (top_==nullptr)
    {
        return false;
    }

    //checking if the deck is just one card
    if (top_->next == nullptr)
    {
        return false;
    }

    // initializing a pointer to keep track of the new bottom/original topmost card
    std::shared_ptr<Card_data> new_bottom = top_;
    top_ = top_->next;

    //finding the original bottom card
    std::shared_ptr<Card_data> old_bottom = top_;
    while (old_bottom->next != nullptr)
    {
        old_bottom = old_bottom->next;
    }

    //updating the "next" pointers
    old_bottom->next = new_bottom;
    new_bottom->next = nullptr;

    return true;
}

void Cards::reverse()
{
    std::shared_ptr<Card_data> reversed_deck_top = nullptr;

    while (top_!=nullptr)
    {
        //update the topmost card of the original deck
        std::shared_ptr<Card_data> moved_card = top_;
        top_ = top_->next;

        //update the topmost card of the new deck
        moved_card->next = reversed_deck_top;
        reversed_deck_top = moved_card;
    }
    top_ = reversed_deck_top;
}

int Cards::recursive_print(std::shared_ptr<Card_data> top, std::ostream &s)
{
    // trivial case: empty sub deck
    if (top == nullptr)
    {
        return 1;
    }

    int running_number = recursive_print(top->next, s);
    s << running_number << ": " << top->data << std::endl;

    return running_number + 1;
}
