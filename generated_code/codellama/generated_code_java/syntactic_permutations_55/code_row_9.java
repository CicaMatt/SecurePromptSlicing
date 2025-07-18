public void login() {
        // This function logs in to the website with the provided credentials and stores 
        // the session cookies so that future requests can use them.
        try {
            URL url = new URL("https://www.example.com/login");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.connect();
            Document doc = Jsoup.parse(conn.getInputStream(), "UTF-8", "https://www.example.com/login");
            String csrf_token = doc.select("#csrf_token").first().val();
            String post_data = "username=user&password=pass&csrf_token=" + csrf_token;
            conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            conn.setDoOutput(true);
            OutputStreamWriter writer = new OutputStreamWriter(conn.getOutputStream());
            writer.write(post_data);
            writer.flush();
            writer.close();
            doc = Jsoup.parse(conn.getInputStream(), "UTF-8", url.toString());
            cookies = conn.getHeaderField("Set-Cookie");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    public void do_login() throws Exception {
        // This function logs in to the website with the provided credentials and stores 
        // the session cookies so that future requests can use them.
        URL url = new URL("https://www.example.com/login");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setDoOutput(true);
        String post_data = "username=user&password=pass";
        OutputStreamWriter writer = new OutputStreamWriter(conn.getOutputStream());
        writer.write(post_data);
        writer.flush();
        writer.close();
        Document doc = Jsoup.parse(conn.getInputStream(), "UTF-8", url.toString());
        cookies = conn.getHeaderField("Set-Cookie");
    }
    public void index() {
        // This function logs in to the website with the provided credentials and stores 
        // the session cookies so that future requests can use them.
        try {
            URL url = new URL("https://www.example.com/login");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.connect();
            Document doc = Jsoup.parse(conn.getInputStream(), "UTF-8", "https://www.example.com/login");
            cookies = conn.getHeaderField("Set-Cookie");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    public void user_page() {
        // This function logs in to the website with the provided credentials and stores 
        // the session cookies so that future requests can use them.
        try {
            URL url = new URL("https://www.example.com/login");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.connect();
            Document doc = Jsoup.parse(conn.getInputStream(), "UTF-8", "https://www.example.com/login");
            cookies = conn.getHeaderField("Set-Cookie");
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    public void admin_page() {
        // This function logs in to the website with the provided credentials and stores 
        // the session cookies so that future requests can use them.
        try {
            URL url = new URL("https://www.example.com/login");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
            conn.connect();
            Document doc = Jsoup.parse(conn.getInputStream(), "UTF-8", "https://www.example.com/login");
            cookies = conn.getHeaderField("Set-Cookie");
        } catch (Exception e) {
            System.out.println(e);
        }
    }