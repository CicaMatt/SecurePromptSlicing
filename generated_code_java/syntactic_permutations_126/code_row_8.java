import java.io.*;  

    public class Http_hello_page {  
        private static String username;  
        public static void main(String[] args) throws IOException {  
            BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));  
            StringBuilder outputbuf=new StringBuilder();  
            BufferedWriter writer=new BufferedWriter(new OutputStreamWriter(System.out));  

            while ((username = reader.readLine()) != null) {  
                outputbuf.append("<HTML><BODY> Hello " + username + "</BODY></HTML>");  
                writer.write(outputbuf);  
                writer.close();  
            }  
        }
    }