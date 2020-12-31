#include "./controller/MyController.hpp"
#include "./AppComponent.hpp"
#include "oatpp/network/Server.hpp"
#include <iostream>
#include "oatpp-swagger/Controller.hpp"
#include "controller/AcquisitionController.hpp"

void run()
{
   /* Register Components in scope of run() method */
   AppComponent components;

   /* Get router component */
   OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

   /* Create MyController and add all of its endpoints to router */
   auto myController = std::make_shared<MyController>();
   myController->addEndpointsToRouter(router);

   auto acquisitionController = std::make_shared<CAcquisitionController>();
   acquisitionController->addEndpointsToRouter(router);

   /* Get connection handler component */
   OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

   /* Get connection provider component */
   OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

   auto docEndpoints = oatpp::swagger::Controller::Endpoints::createShared();
   //docEndpoints->pushBackAll(myController->getEndpoints());
   docEndpoints->pushBackAll(acquisitionController->getEndpoints());

   auto swaggerController = oatpp::swagger::Controller::createShared(docEndpoints);
   swaggerController->addEndpointsToRouter(router);

   /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
   oatpp::network::Server server(connectionProvider, connectionHandler);

   /* Priny info about server port */
   OATPP_LOGI("Yadoms ", "Server running on port %s", connectionProvider->getProperty("port").getData());

   /* Run server */
   server.run();
}

/**
 *  main
 */
int main(int argc, const char* argv[])
{
   oatpp::base::Environment::init();

   run();

   /* Print how much objects were created during app running, and what have left-probably leaked */
   /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
   std::cout << "\nEnvironment:\n";
   std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
   std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

   oatpp::base::Environment::destroy();

   return 0;
}
