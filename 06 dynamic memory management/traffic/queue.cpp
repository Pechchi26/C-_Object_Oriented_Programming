#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle): cycle_(cycle)
{

}

void Queue::enqueue(const string &reg)
{
    if (is_green_) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        dequeue();
    } else {
        shared_ptr<Vehicle> new_vehicle = make_shared<Vehicle>();
        new_vehicle->reg_num = reg;
        new_vehicle->next = nullptr;

        if (first_ == nullptr) {
            first_ = new_vehicle;
            last_ = new_vehicle;
        } else {
            last_->next = new_vehicle;
            last_ = new_vehicle;
        }
    }
}

void Queue::switch_light()
{
    is_green_ = !is_green_;

    if (is_green_) {
        cout << "GREEN: ";

        if (first_ == nullptr) {
            cout << "No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "Vehicle(s)";
            unsigned int count = 0;

            while (count < cycle_ && first_ != nullptr) {
                cout << " " << first_->reg_num;
                dequeue();
                ++count;
            }
            cout << " can go on" << endl;
            is_green_ = false;
        }
    } else {
        print();
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    if (is_green_) {
        cout << "GREEN: ";
    } else {
        cout << "RED: ";
    }

    if (first_ == nullptr) {
        cout << "No vehicles waiting in traffic lights" << endl;
    } else {
        cout << "Vehicle(s)";
        std::shared_ptr<Vehicle> current = first_;

        while (current != nullptr) {
            cout << " " << current->reg_num;
            current = current->next;
        }
        cout << " waiting in traffic lights" << endl;
    }
}

void Queue::dequeue()
{
    if (is_green_ && first_ != nullptr) {
        shared_ptr<Vehicle> current = first_;
        first_ = first_->next;

        if (first_ == nullptr) {
            last_ = nullptr;
        }
    }
}

