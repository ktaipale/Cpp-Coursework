#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    cycle_(cycle)
{

}

Queue::~Queue()
{
    Vehicle *current_vehicle = first_;
    while(current_vehicle != nullptr)
    {
        first_ = first_->next;
        delete current_vehicle;
        current_vehicle = first_;
    }
}

void Queue::enqueue(const string &reg)
{
    if(is_green_)
    {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
    }
    else
    {
        Vehicle *car = new Vehicle();
        car->reg_num = reg;
        if (first_ == nullptr)
        {
            first_ = car;
            last_ = car;
        }
        else
        {
            last_->next = car;
            last_ = car;
        }
    }
}

void Queue::switch_light()
{
    Vehicle *current_vehicle = first_;
    if (is_green_)
    {
        is_green_ = false;
        std::cout << "RED:";
    }
    else
    {
        is_green_ = true;
        std::cout << "GREEN:";
    }

    if(current_vehicle == nullptr)
    {
        std::cout << " No vehicles waiting in traffic lights" << std::endl;
    }
    else
    {
        std::cout << " Vehicle(s)";
        int i = cycle_;
        while(i > 0 and current_vehicle != nullptr)
        {
            std::cout << " " << current_vehicle->reg_num;
            first_ = first_->next;
            Dequeue(current_vehicle);
            current_vehicle = first_;
            i--;
        }
        std::cout << " can go on" << std::endl;
        is_green_ = false;
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    Vehicle *current_vehicle = first_;
    if (!is_green_)
    {
        std::cout << "RED: ";
    }
    else
    {
        std::cout << "GREEN: ";
    }
    if (current_vehicle != nullptr)
    {
        std::cout << "Vehicle(s)";
        while(current_vehicle != nullptr)
        {
            std::cout << " " << current_vehicle->reg_num;
            current_vehicle = current_vehicle->next;
        }
        if(!is_green_)
        {
            std::cout << " waiting in traffic lights" << std::endl;
        }
        else
        {
            std::cout << " can go on" << std::endl;
        }
    }
    else
    {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
    }
}

void Queue::Dequeue(Vehicle* &current_vehicle)
{
    delete current_vehicle;
}
