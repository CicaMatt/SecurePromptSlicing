import java.io.*; 
    import java.net.*;
    public class ProductPrice {

        int price = 12; // default price for product code xyz

        public static void main(String[] args) {
            try {
                ServerSocket serverSocket = new ServerSocket(5000);
                System.out.println("Server started");
                while (true) {
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("Client connected");

                    InputStreamReader isr = new InputStreamReader(clientSocket.getInputStream());
                    BufferedReader br = new BufferedReader(isr);

                    String productCode = br.readLine();
                    int quantity = Integer.parseInt(br.readLine());

                    double price = calculatePriceForProductCodeAndQuantity(productCode, quantity);
                    
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                    String response = "The total price for the product code " + productCode + " and quantity " + quantity + " is " + price;
                    out.println(response);

                    clientSocket.close();
                }
            } catch (Exception e) {
                System.out.println("Error:" + e.getMessage());
            }
        }

        public static double calculatePriceForProductCodeAndQuantity(String productCode, int quantity) {
            if (productCode.equals("abc")) {
                return 10 * quantity;
            } else if (productCode.equals("xyz")) {
                return 5 * quantity;
            }
            return -1; // error
        }
    }