public class Http {
      static void http_hello_page(FileInputStream request, FileOutputStream response) {
        // Read the username from the request
        String username = readUsername(request);
        // Construct the response message
        String responseMessage = "Hello " + username;
        // Write the response to the response file stream
        writeResponse(response, responseMessage);
      }
    
      private static String readUsername(FileInputStream request) {
        return "username";
      }
    
      private static void writeResponse(FileOutputStream response, String responseMessage) {
        // Write the response to the response file stream
      }
    }