public class HelloServer {  
        public void http_hello_page(HttpExchange t) throws IOException{  
            String input = "";  
            InputStreamReader isr = new InputStreamReader(t.getRequestBody(), "utf-8");  
            BufferedReader br = new BufferedReader(isr);  
            String username;  
            while ((username = br.readLine()) != null) {  
                input += username + "\n";  
            }  
            String outputbuf = "<html><body>" + input + "</body></html>";  
            t.sendResponseHeaders(200, outputbuf.length());  
            OutputStream os = t.getResponseBody();  
            os.write(outputbuf.getBytes(), 0, outputbuf.length());  
            os.close();  
        }  
    }