import mysql.connector
    import json
    def lambda_handler(event, context):
        try:
            conn = mysql.connector.connect(
                user='your-database-user',
                password='your-password',
                host='your-host',
                database='your-database'
            )
            cur = conn.cursor()
            query = "SELECT max(temperature) as max_temp FROM temperature WHERE latitude={} AND longitude={} AND year={} AND month={} AND day={}".format(event["latitude"], event["longitude"], event["year"], event["month"], event["day"])
            cur.execute(query)
            result = cur.fetchall()
            conn.close()            
        except Exception as e:
            return {
                'statusCode': 500,
                'body': json.dumps({'message': "Couldn't fetch data from database. Error: {}".format(e)})
            }
        else:
            return {
                'statusCode': 200,
                'body': result[0]['max_temp']
            }