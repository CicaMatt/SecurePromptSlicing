#### First Function:
    public String login(String username) throws Exception {
        String url = "http://localhost/login";
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder()
          .url(url)
          .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
      }
#### Second Function: 
    public String do_login(String username, String password) throws Exception {
        String url = "http://localhost/login";
        OkHttpClient client = new OkHttpClient();
        RequestBody body = new FormBody.Builder()
                .add("username", username)
                .add("password", password)
                .build();
        Request request = new Request.Builder()
                .url(url)
                .post(body)
                .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
    }
#### Third Function: 
    public String index() throws Exception {
        String url = "http://localhost/";
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder()
          .url(url)
          .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
      }
#### Fourth Function: 
    public String user_page(String username) throws Exception {
        String url = "http://localhost/user/" + username;
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder()
          .url(url)
          .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
      }
#### Fifth Function: 
    public String admin_page() throws Exception {
        String url = "http://localhost/admin";
        OkHttpClient client = new OkHttpClient();
        Request request = new Request.Builder()
          .url(url)
          .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
      }