package com.google.engedu.productsearch;

import android.content.Context;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

class Product {
    private String mTitle;
    private String mPrice;
    public Product(String title, String price) {
        mTitle = title;
        mPrice = price;
    }
    public String getTitle() {
        return mTitle;
    }
    public String getPrice() {
        return mPrice;
    }
}

class ProductSearchActivity {
    private static final String TAG = "ProductSearchActivity";
    private Context context;
    private List<Product> products = new ArrayList<>();

    public ProductSearchActivity(Context context) {
        this.context = context;
    }

    public void calculatePrice() {
        try {
            String urlParameters  = "product_id=45215&quantity=3";
            byte[] postData       = urlParameters.getBytes();
            int    postDataLength = postData.length;
            String request        = "https://www.example.com/calculateprice";
            URL    url            = new URL(request);
            HttpURLConnection conn= (HttpURLConnection) url.openConnection();            conn.setDoOutput(true);
            conn.setInstanceFollowRedirects(false);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            conn.setRequestProperty("charset", "utf-8");
            conn.setRequestProperty("Content-Length", Integer.toString(postDataLength));
            conn.setUseCaches(false);
            try (BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()))) {
                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    Log.d(TAG, "URL Content: " + inputLine);
                    products.addAll(parseProducts(inputLine));
                }
            } catch (IOException ex) {
                Log.e(TAG, "Failed to fetch data: ", ex);
            }
        } catch (MalformedURLException e) {
            Log.e(TAG, "Invalid URL");
        } catch (IOException e) {
            Log.e(TAG, "IO Error");
        }
    }

    private List<Product> parseProducts(String inputLine) {
        // Use a JSON parser to extract the product details and create a list of Product objects
        return null;
    }
}