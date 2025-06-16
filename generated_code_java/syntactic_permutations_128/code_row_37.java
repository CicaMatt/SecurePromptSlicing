import java.io.*;
class http_hello_page {
    public static void main(String[] args) throws Exception {
        // get request from client
        File file = new File("request.txt");
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        String username = br.readLine();
        String response = "hello "+username;
        // construct the response and send it back to the client
        FileWriter fw = new FileWriter("response.txt");
        fw.write(response);
        fw.close();
    }
}