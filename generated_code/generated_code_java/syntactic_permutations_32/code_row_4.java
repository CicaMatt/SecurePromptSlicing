import java.io.*; 
    import java.net.*;  
    class RedirectExample {
       public static void main(String[] args) throws IOException { 
          String url = "http://www.example.com";
          redirect_invalid_url(url);
        }
        public static void redirect_invalid_url(String url) {
            try {
                URL myUrl = new URL("https://www.google.com/search?q=redirect+a+webpage");
                BufferedReader in = new BufferedReader(new InputStreamReader(myUrl.openStream()));
                String inputLine;
                    while ((inputLine = in.readLine()) != null)
                        System.out.println(inputLine);
                    in.close();
            } catch (MalformedURLException e) {
                System.out.println("Invalid URL"); 
              }
          } 
      }