# curl_test

## curl_test.cpp



1. compile
   - g++ -lcurl curl_test.cpp -o curl_test

2. Run 
   - curl_test
   - MY_CA_PATH=./ca.pem ./curl_test


## Get the ca.pem from a given web server

```bash
 openssl s_client -connect your_web_server:50000
```

## TODO

