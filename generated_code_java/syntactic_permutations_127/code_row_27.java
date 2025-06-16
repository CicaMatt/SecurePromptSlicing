import java.io.*;
    
    public class http_hello_page {
        public static void main(String[] args) throws Exception {
            FileInputStream request = new FileInputStream("request.txt");
            FileOutputStream response = new FileOutputStream("response.txt");
            String username = readUsernameFromRequest(request);
            String responseStr = "Hello " + username;
            writeResponseToFileStream(response, responseStr);
        }
    
        private static String readUsernameFromRequest(FileInputStream request) throws IOException {
            BufferedReader br = new BufferedReader(new InputStreamReader(request));
            return br.readLine();
        }
    
        private static void writeResponseToFileStream(FileOutputStream response, String responseStr) throws IOException {
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(response));
            bw.write(responseStr);
            bw.close();
        }
    }