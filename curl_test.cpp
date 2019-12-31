#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void CheckError(CURLcode err)
{
	if(err != 0)
	{
		std::string errMsg(curl_easy_strerror(err));
		cout << "error code: " << err << ", error message: " << errMsg << endl;
		exit(1);
	}
}

int main(void)
{
	CURL *curl;
	CURLcode ret = CURLE_OK;
	std::string readBuffer;

	curl = curl_easy_init();
	if(!curl)
	{
		cout << "init error" << endl;
		return 0;
	}

	ret = curl_easy_setopt(curl, CURLOPT_URL, "https://CNPVGVB1CIH34:50000/b1s/v1/Login");
	CheckError(ret);

	ret = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	CheckError(ret);

	ret = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	CheckError(ret);

	const char* MY_CA_PATH = "MY_CA_PATH";
	char *caPath = getenv(MY_CA_PATH);
	if(caPath)
	{
		// ret = curl_easy_setopt(curl, CURLOPT_CAPATH, sldCAPath);
		// CheckError(ret);

		ret = curl_easy_setopt(curl, CURLOPT_CAINFO, caPath);
		CheckError(ret);
	}
	else
	{
		ret = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		CheckError(ret);

		ret = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		CheckError(ret);
	}
	
	ret = curl_easy_perform(curl);
	CheckError(ret);

	curl_easy_cleanup(curl);
	std::cout << readBuffer << std::endl;
	return 0;
}

//g++ -lcurl curl_test.cpp -o curl_test
//curl_test
//MY_CA_PATH=./ca.pem ./curl_test
