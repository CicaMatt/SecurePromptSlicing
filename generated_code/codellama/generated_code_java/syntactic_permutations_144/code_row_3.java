package com.mycompany.unsubscribe;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Unsubscriber {

  public boolean unsubscribeEmail(String email) throws Exception {
    // check if the email exists in the database
    int emailExist = emailExist(email);
    if (emailExist == 0) {
      return false;
    } else {
      // call a script that unsubscribes the email. If it returns 1, it means that the email has been successfully
      // unsubscribed, otherwise it returns 0 meaning that there was an error during the unsubscription process.
      int unsubscribe = unsubscribe(email);
      if (unsubscribe == 1) {
        return true;
      } else {
        return false;
      }
    }
  }

  public int emailExist(String email) throws SQLException {
    Connection connection = null;
    Statement statement = null;
    ResultSet resultSet = null;
    try {
      connection = getConnection();
      String queryEmailExist = "SELECT * FROM subscriptions WHERE email='" + email + "'";
      statement = connection.createStatement();
      resultSet = statement.executeQuery(queryEmailExist);
      if (resultSet.next()) {
        return 1;
      } else {
        return 0;
      }
    } catch (SQLException e) {
      throw new SQLException("Error when checking if email exists", e);
    } finally {
      close(connection, statement, resultSet);
    }
  }

  public int unsubscribe(String email) throws Exception {
    // call a script to unsubscribe the email and return 1 on success or 0 if there was an error.
    // this method should be implemented in another file.
    throw new UnsupportedOperationException("Not supported yet.");
  }

  public Connection getConnection() throws SQLException {
    // establish connection with database.
    // this method should be implemented in another file.
    throw new UnsupportedOperationException("Not supported yet.");
  }

  public void close(Connection connection, Statement statement, ResultSet resultSet) throws SQLException {
    if (resultSet != null) {
      try {
        resultSet.close();
      } catch (SQLException e) {
        throw new SQLException("Error when closing result set", e);
      }
    }
    if (statement != null) {
      try {
        statement.close();
      } catch (SQLException e) {
        throw new SQLException("Error when closing statement", e);
      }
    }
    if (connection != null) {
      try {
        connection.close();
      } catch (SQLException e) {
        throw new SQLException("Error when closing connection", e);
      }
    }
  }
}