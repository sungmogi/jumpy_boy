#include "controller.hxx"

int
main()
{
    Model model;
    Controller controller(model);
    controller.run();

    return 0;
}
