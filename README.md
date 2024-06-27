# Console-Based Social Network Application in C++ (OOP)

## Introduction

This project is a console-based social network application developed in C++ using Object-Oriented Programming (OOP) principles. It simulates basic social network functionalities such as managing users, friends, pages, posts, activities, and comments.

## How to Run

Place the Source.cpp file and all txt files in same folder and run cpp file


## Project Description

The application includes the following features:

### Users

- Each user has a unique ID and name.
- A user can have up to 10 friends.
- A user can like up to 10 pages.

### Pages

- Each page has a unique ID, title, a list of posts (page’s timeline), and the total number of people who have liked it.

### Posts

- Each post has a unique ID, description/text, number of likes, a list of people who have liked it, and a shared date.
- A post can have up to 10 comments.

### Activities

- An activity can be a part of a post, with types and values as shown in the table below:

| Type             | Value                              |
| ---------------- | ---------------------------------- |
| feeling          | Happy/sad/excited etc.             |
| thinking about   | life/future/meaning of life etc.   |
| making           | Money/art/memories etc.            |
| celebrating      | A birthday/Halloween/success etc.  |

### Memories

- A memory is a post having a pointer to the original post.

### Comments

- A comment is posted by a specific user or page.

## Functionalities

### Set Current User

- The program will Ask the user about their ID and set them as the current user of the application. Now everything that is seen in the system will be from the perspective of this user.

### View Home of Current User

- It contains posts of all friends shared in the last 24 hours and posts of all liked pages shared in the last 24 hours.

### Like a Post

- Current user can like the post by using post id.

### View the List of People Who Liked a Post

- Current user can view who have liked the post by using post id.

### Comment on a Post

- Current user can comment on a post by using post id.

### View a Post

- Current user can view the post and comments on this post by using post id.


### View User’s Timeline

- Current user can see its user's name and posts in their timeline.

### View Friend List

- Current user can see friend list of users by using user id


