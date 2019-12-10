# Mycorp Greeting
An example module to create custom services in Drupal 7

## Goals
1. Creates greetings content type along with the required fields
2. Creates Rest server resource named "Greeting" with CRUD operation and a publish action
3. Allows users to create, update, delete, fetch, publish and unpublish Greeting content using REST API

## Installation
Install greetings_feature and mycorp_greeting like any other Drupal module and create greeting content to play around with the API.

## REST API Documentation

### Retrieve greeting
  Return a specific greeting of given id.

* **URL**

  `api/v1/greetings/{id}`

* **Method:**  
  `GET`
  
*  **URL Params**

   **Required:**
   `id=[integer]` - ID of the greeting to return

* **Success Response:**
  
  Returns the greeting content field values.

  * **Code:** 200 <br />
    **Content:** `{
    "uid": "1",
    "title": "Test greeting 1",
    "log": "",
    "status": "1"
    }`
 
* **Error Response:**

  * **Code:** 404 NOT FOUND <br />
    **Content:** `{ error : "Greeting not found" }`

### Create greeting
  Create a new greeting. Need to login using `api/v1/user/login` and obtain the token to create a new greeting

* **URL**

  `api/v1/greetings`

* **Method:**  
  `POST`
  
*  **Data Params**

   **Required:**
   `title=[text]` - Title of the greeting to be created
   
   **optional:**
   `field_greeting_image=[url]` - Image URL for the greeting to be created

* **Success Response:**
  
  Returns the created greeting nid.

  * **Code:** 200 <br />
    **Content:** `1`
 
* **Error Response:**

  * **Code:** 401 UNAUTHORIZED <br />
    **Content:** `{ error : "Log in" }`

### Delete greeting
  Delete a specific greeting of given id.

* **URL**

  `api/v1/greetings/{id}`

* **Method:**  
  `DELETE`
  
*  **URL Params**

   **Required:**
   `id=[integer]` - ID of the greeting to delete

* **Success Response:**
  
  Returns **TRUE**
  
* **Error Response:**

   * **Code:** 401 UNAUTHORIZED <br />
    **Content:** `{ error : "Log in" }`
    
### Update greeting
  Update a greeting of given id. Need to login using `api/v1/user/login` and obtain the token to update a greeting

* **URL**

  `api/v1/greetings/{id}`

* **Method:**  
  `PUT`
  
*  **URL Params**

   **Required:**
   `id=[integer]` - ID of the greeting to update

*  **Data Params**

   `title=[text]` - Title of the greeting to be created
   `field_greeting_image=[url]` - Image URL for the greeting to be created

* **Success Response:**
  
  Returns the updated greeting values.

  * **Code:** 200 <br />
    **Content:** `{
    "uid": "1",
    "title": "Test greeting 1",
    "log": "",
    "status": "1"
    }`
 
* **Error Response:**

  * **Code:** 401 UNAUTHORIZED <br />
    **Content:** `{ error : "Log in" }`

### Publish / unpublish greeting
  Publish / unpublish a specific greeting of given id.

* **URL**

  `api/v1/greetings/{id}/publish`

* **Method:**  
  `POST`
  
*  **URL Params**

   **Required:**
   `id=[integer]` - ID of the greeting to publish / unpublish

* **Success Response:**
  
  Returns **TRUE**
  
* **Error Response:**

   * **Code:** 401 UNAUTHORIZED <br />
    **Content:** `{ error : "Log in" }`
