import java.io.*; 
     public class Main {
        public static void http_hello_page(FileInputStream request, FileOutputStream response) throws IOException {
            String username = "";
            int ch;
            while((ch=request.read())!=-1){
                if (ch=='\n'){
                    break;
                } else {
                    username += (char)ch;
                }
            }
            response.write(("Hello "+username).getBytes());
        }
     }