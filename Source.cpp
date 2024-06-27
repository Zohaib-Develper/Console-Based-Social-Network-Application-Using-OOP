
#include<iostream>
#include<fstream>
using namespace std;
class Date;
class Activity;
class Object;
class Comment;
class Post;
class Memory;
class User;
class Page;
class Facebook;

class Helper
{
public:
	static int StringLenght(const char* str)
	{
		int lenght = 0;
		for (lenght = 0; str[lenght] != '\0'; lenght++);
		return lenght;
	}

	static void StringCopy(char*& dest, const char* src)
	{
		if (dest != nullptr)
			delete[] dest;
		dest = nullptr;
		int len = StringLenght(src);
		dest = new char[len + 1];
		for (int i = 0; i < len; i++)
		{
			dest[i] = src[i];
		}
		dest[len] = '\0';
	}

	static char* GetStringFromBuffer(char* str)
	{
		char* newString = nullptr;
		StringCopy(newString, str);
		return newString;
	}
	static bool Compare(const char* lhs, const char* rhs)
	{
		int len1 = 0, len2 = 0;
		len1 = StringLenght(lhs);
		len2 = StringLenght(rhs);
		if (len1 != len2)
		{
			return 0;
		}
		for (int j = 0; lhs[j] != '\0' && rhs[j] != '\0'; j++)
		{

			if (lhs[j] != rhs[j])
			{
				return 0;
			}
		}
		return 1;

	}
	static char* createID(const char* temp,int n)
	{
		int count = 0;//To count number of digits in a number
		int length = Helper::StringLenght(temp);

		for (int i = n; i > 0;)
		{
			i = i / 10;
			count++;
		}

		char* id = new char[length + count + 1];

		int i;
		for (i = 0; temp[i]!='\0'; i++)
		{
			id[i] = temp[i];
		}

		
		for (i=length+count; i >length; i--)
		{
			id[i-1] = 48 + n%10;
			n = n / 10;
		}
		id[length+count] = '\0';
		return id;

	}
};
class Date
{

private:
	int day;
	int month;
	int year;


public:
	static Date CurrentDate;
	Date(int d = 0, int m = 0, int y = 0)
	{
		day = d;
		month = m;
		year = y;

	}
	static void SetCurrentDate(int d = 0, int m = 0, int y = 0)
	{
		CurrentDate.day = d;
		CurrentDate.month = m;
		CurrentDate.year = y;
	}
	void ReadData(istream& fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}
	void Print()
	{
		cout << "( " << day << "/" << month << "/" << year << " )" ;
	}
	bool IfLatest()//To check if given date is equal to or 1 day less than current date
	{
		if (CurrentDate.day - 1 == 0)
		{
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				if (day == 31)
				{
					return 1;
				}
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day == 30)
				{
					return 1;
				}

			}
			else
			{
				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				{
					if (day == 29)
					{
						return 1;
					}
				}
				else 
				{
					if (day == 28)
					{
						return 1;
					}
				}

			}
		}
		else
		{
			if (day == CurrentDate.day || day == CurrentDate.day - 1)
			{
				return 1;
			}
		}
		return 0;
	}
	bool IsEqualToCurrent()//To check if day and month of given date is equal to that current date
	{
		return (day == CurrentDate.day && month == CurrentDate.month);
	}
	int GetYear()
	{
		return year;
	}
};
Date Date::CurrentDate;

class Activity
{

private:
	int type;
	char* description;
public:
	Activity()
	{
		type = 0;
		description = nullptr;
	}
	void ReadActivity(istream& fin)
	{
		fin >> type;
		char temp[80];
		fin.getline(temp, 80);
		description = Helper::GetStringFromBuffer(temp);
	}
	void PrintActivity()
	{
		cout << "is ";
		if (type == 1)
		{
			cout << "feeling ";
		}
		if (type == 2)
		{
			cout << "thinking about ";
		}
		if (type == 3)
		{
			cout << "making ";
		}
		if (type == 4)
		{
			cout << "celebrating ";
		}
		cout << description;
	}
	~Activity()
	{
		if (description)
			delete[] description;
	}
};
class Object
{
	protected:
		char* ID;
public:
	Object()
	{
		ID = nullptr;
	}

	virtual void Print() = 0 {}
	virtual void AddPost(Post* shared) = 0 {}
	virtual char* GetID() = 0 {}
	virtual ~Object()
	{
		if (ID)
			delete[] ID;
	}
};
class Comment
{
private:
	char* ID;
	char* text;
	Object* commentby;
public:
	Comment()
	{
		ID = nullptr;
		text = nullptr;
		commentby = nullptr;
	}
	void SetValue(char* id,char* t, Object* commenter)
	{
		ID = id;
		text = t;
		commentby = commenter;
	}
	void PrintComments()
	{
		commentby->Print();

		cout << " wrote: \"";
		cout << text << "\"";
	}
	~Comment()
	{
		if (ID)
			delete[] ID;
		if (text)
			delete[] text;
	}
};
class Post
{
private:
	int type;//To store the type of Post i.e. Activity or simple post. 1 for simple post and 2 for activity
	char* ID;
	char* caption;
	int noOfLikes;
	int noOfComments;
	Date dateOfSharing;
	Activity* activity;
	Object* sharedBy;
	Object** likedBy;
	Comment** comments;
	static int maxlikes;
	static int maxComments;


public:
	Post()
	{
		type = 0;
		ID = nullptr;
		caption = nullptr;
		noOfLikes = 0;
		noOfComments = 0;
		activity = nullptr;
		sharedBy = nullptr;
		likedBy = nullptr;
		comments = nullptr;

	}
	void ReadDataFromFile(ifstream& fin)
	{
		fin >> type;
		char temp[100];

		fin >> temp;
		ID = Helper::GetStringFromBuffer(temp);
		dateOfSharing.ReadData(fin);
		fin.seekg(2, ios::cur);
		fin.getline(temp, 100);

		caption = Helper::GetStringFromBuffer(temp);
		if (type == 2)
		{
			activity = new Activity;
			activity->ReadActivity(fin);
		}
	}
	void SetSharedBy(Object* temp)
	{
		sharedBy = temp;
	}
	void SetLikedBy(Object* temp)
	{
		if (noOfLikes < maxlikes)
		{
			if (noOfLikes == 0 && likedBy == nullptr)
			{
				likedBy = new Object * [maxlikes];
				likedBy[noOfLikes++] = temp;
			}
			else
			{
				likedBy[noOfLikes++] = temp;
			}
		}
		else
		{
			cout << "\n\n----------- A post can be liked by " << maxlikes << " users at max------------\n\n";
		}
	}
	char* GetID()
	{
		return ID;
	}
	void AddComment(Comment* ptr)
	{
		if (noOfComments < maxComments)
		{
			if (noOfComments == 0 && comments == nullptr)
			{
				comments = new Comment * [maxComments];
				comments[noOfComments++] = ptr;
			}
			else
			{
				comments[noOfComments++] = ptr;
			}
		}
		else
		{
			cout << "\n\n---------- A post can have " << maxComments << " comments at amx----------\n\n";
		}
	}
	virtual void Print(bool commentsCheck=true,bool dateCheck=true)//To Print Posts
	{
		if (type == 0)
		{
			cout << "\n----";
			sharedBy->Print();
			cout << " shared a memory----";
			cout << endl;
		}
		else
		{
			sharedBy->Print();
			cout << " ";
			if (type == 2)
			{
				activity->PrintActivity();
				cout << endl;
			}
			else
			{
				cout << "Shared ";
			}
		}
		cout << "\"" << caption << "\"";
		if (dateCheck)
		{
			cout << "...";
			dateOfSharing.Print();
		}

		if (commentsCheck)
		{
			cout << endl;
			for (int i = 0; i < noOfComments; i++)
			{
				cout << "\t\t\t";
				comments[i]->PrintComments();
				cout << endl;
			}
			cout << endl;
		}
	}
	void ViewLikedList()
	{
		cout << endl;
		if(likedBy)
		for (int i = 0; i < noOfLikes; i++)
		{
			cout << likedBy[i]->GetID() << " - ";
			likedBy[i]->Print();
			cout << endl;
		}
	}
	void ShareMemory(char* id,Object* temp, char* title)
	{
		ID = id;
		sharedBy = temp;
		caption = title;
		dateOfSharing = Date::CurrentDate;
	}
	Date GetDateOfSharing()
	{
		return dateOfSharing;
	}
	virtual ~Post()
	{

			if (ID)
				delete[] ID;
			if (caption)
				delete[] caption;
			if (activity)
				delete activity;
			if (sharedBy)
				sharedBy = nullptr;
			if (likedBy)
				delete[] likedBy;
			if (comments)
			{
				for (int i = 0; i < noOfComments; i++)
					delete comments[i];
				delete[] comments;
			}
	}
};

int Post::maxlikes = 10;
int Post::maxComments = 10;

class Memory : public Post
{
private:
	Post* previuosPost;
public:
	Memory(Post* temp)
	{
		previuosPost = temp;
	}
	void Print(bool commentsCheck = true, bool dateCheck = true)
	{
		Post::Print(commentsCheck,dateCheck);
		cout << "\t\t\t(";
	    cout<<Date::CurrentDate.GetYear()-(previuosPost->GetDateOfSharing()).GetYear();
		cout << " years ago)\n";
		previuosPost->Print(0,dateCheck);
	}
	~Memory()
	{
		previuosPost = nullptr;
	}
};

class Page :public Object
{
private:
	
	char* title;
	Post** posts;
	static int maxPostsofPages;
	int noOfPosts;
public:
	Page()
	{

		title = nullptr;
		posts = nullptr;
		noOfPosts = 0;
	}
	void ReadDataFromFile(ifstream& fin)
	{
		char temp[50];
		fin >> temp;
		ID = Helper::GetStringFromBuffer(temp);

		fin.seekg(1, ios::cur);
		fin.getline(temp, 50);
		title = Helper::GetStringFromBuffer(temp);

	}

	void Print()
	{
		cout << title;
	}

	void AddPost(Post* shared)
	{
		if (noOfPosts < maxPostsofPages)
		{
			if (noOfPosts == 0 && posts == nullptr)
			{
				posts = new Post * [maxPostsofPages];
				posts[noOfPosts++] = shared;
			}
			else
			{
				posts[noOfPosts++] = shared;
			}
		}
		else
		{
			cout << "\n\n------------A page can have " << maxPostsofPages << " posts at max----------\n\n";
		}
	}
	char* GetID()
	{
		return ID;
	}
	void PrintLatestPost()
	{
		if(posts)
		for (int i = 0; i < noOfPosts; i++)
		{
			if ((posts[i]->GetDateOfSharing()).IfLatest())
			{
				posts[i]->Print(1,0);
				cout << endl;
			}
		}
	}
	void PrintPosts()
	{
		cout << endl;
		if(posts)
		for (int i = 0; i < noOfPosts; i++)
		{
			posts[i]->Print();
			cout << endl << endl;
		}
	}
	~Page()
	{
		if (title)
			delete[] title;

		if (posts)
		{
			for (int i = 0; i < noOfPosts; i++)
				delete posts[i];
			delete[] posts;
		}
	}
};
int Page::maxPostsofPages = 10;

class User :public Object
{
private:

	char* FName;
	char* LName;
	int noOfLikedPages;//To store the number of Pages user has liked
	int noOffriends;//To store the number of friends user has
	int noOfPosts;
	User** friends;
	Page** likedPages;
	Post** posts;
	static int maxfriends;//Maximum no of friends a User can have
	static int maxpages;//Maximum no of Pages a User can like
	static int maxlikes;//To store the maximum number of users who can like a post
	static int maxPostsforUser;
public:
	User()
	{
		FName = nullptr;
		LName = nullptr;
		noOfLikedPages = 0;
		noOffriends = 0;
		noOfPosts = 0;
		friends = nullptr;
		likedPages = nullptr;
		posts = nullptr;


	}
	void ReadDataFormFile(ifstream& fin)
	{
		char temp[50];
		fin >> temp;
		ID = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		FName = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		LName = Helper::GetStringFromBuffer(temp);

	}

	void AddLikedPages(Page* like)
	{
		if (noOfLikedPages < maxpages)
		{
			if (noOfLikedPages == 0 && likedPages == nullptr)
			{
				likedPages = new Page * [maxpages];
				likedPages[noOfLikedPages++] = like;
			}
			else
			{
				likedPages[noOfLikedPages++] = like;
			}
		}
		else
		{
			cout << "\n\n-------------A user can like " << maxpages << " pages at max---------- - \n\n";
		}

	}
	void AddFriends(User* facefriend)
	{
		if (noOffriends < maxfriends)
		{
			if (noOffriends == 0 && friends == nullptr)
			{
				friends = new User * [maxfriends];
				friends[noOffriends++] = facefriend;
			}
			else
			{
				friends[noOffriends++] = facefriend;
			}
		}
		else
		{
			cout << "\n\n---------------- A user can have " << maxfriends << " friends at max-----------------\n\n";
		}
	}

	void ViewFriendList()
	{
		Print();
		cout << "-Friend List\n\n";

		if(friends)
		for (int i = 0; i < noOffriends; i++)
		{

			cout << friends[i]->ID;
			cout << "-" << friends[i]->FName;
			cout << " " << friends[i]->LName << endl;
		}
	}
	void ViewLikedPages()
	{
		Print();
		cout << "-Liked Pages\n\n";
		if(likedPages)
		for (int i = 0; i < noOfLikedPages; i++)
		{
			cout << likedPages[i]->GetID() << "-";
			likedPages[i]->Print();
			cout << endl;
		}
	}
	void Print()
	{
		cout << FName << " " << LName;
	}
	void AddPost(Post* shared)
	{
		if (noOfPosts < maxPostsforUser)
		{
			if (noOfPosts == 0 && posts == nullptr)
			{
				posts = new Post * [maxPostsforUser];
				posts[noOfPosts++] = shared;
			}
			else
			{
				posts[noOfPosts++] = shared;
			}
		}
		else
		{
			cout << "\n\n----------- A user can have " << maxPostsforUser << " posts at max--------------\n\n";
		}
	}
	char* GetID()
	{
		return ID;
	}
	void ViewTimeLine()
	{
		Print();
		cout << "-TimeLine\n\n";
		if(posts)
		for (int i = 0; i < noOfPosts; i++)
		{
			posts[i]->Print();
		}
	}
	void PrintHome()
	{
		Print();
		cout << "-Home Page\n\n";
		for (int i = 0; i < noOffriends; i++)
		{
			friends[i]->PrintLatestPost();
		}
		for (int i = 0; i < noOfLikedPages; i++)
		{
			likedPages[i]->PrintLatestPost();
		}

	}
	void PrintLatestPost()
	{
		for (int i = 0; i < noOfPosts; i++)
		{
			if ((posts[i]->GetDateOfSharing()).IfLatest())//If the date of post is equal to or one day less than then this function will return true
			{
				posts[i]->Print(1,0);
				cout << endl;
			}
		}
	}
	void SeeMemories()
	{
		for (int i = 0; i < noOfPosts; i++)
		{
			if ((posts[i]->GetDateOfSharing()).IsEqualToCurrent())
			{
				cout << "\n\nWe hope you enjoy looking backand sharing your memories on Facebook, from the most recent to those long ago";
				cout << "\nOn this Day\n";
				cout << Date::CurrentDate.GetYear() - (posts[i]->GetDateOfSharing()).GetYear();
				cout << " years ago\n";
				cout << "---";
				posts[i]->Print();
			}
		}
	}
	~User()
	{

		if (FName)
			delete[] FName;
		if (LName)
			delete[] LName;
		if (friends)
			delete[] friends;
		if (likedPages)
			delete[] likedPages;
		if (posts)
		{
			for (int i = 0; i < noOfPosts; i++)
				delete posts[i];
			delete[] posts;
		}
	}
};
//int User::noOfUsers = 0;
int User::maxfriends = 10;
int User::maxpages = 10;
int User::maxlikes = 10;
int User::maxPostsforUser = 10;


class Facebook
{

private:
	User** users;
	Page** pages;
	Post** posts;
	Comment** comments;
	int noOfUsers;
	int noOfPages;
	int noOfPosts;
	int noOfComments;

public:
	Facebook()
	{
		users = nullptr;
		pages = nullptr;
		posts = nullptr;
		comments = nullptr;
		noOfUsers = 0;
		noOfPages = 0;
		noOfPosts = 0;
		noOfComments = 0;
	}
	void LoadUsersFromFile(const char* filename)
	{
		ifstream fin(filename);
		if (filename)
		{
			fin >> noOfUsers;

			int maxfriends = 10;//Maximum number of friends a user can have
			int maxPages = 10;//Maximum number of pages a user can like
			int* count = new int[noOfUsers];//To store no of friends a user have

			char*** temp = new char** [noOfUsers];//To store ID of friends in character array

			for (int i = 0; i < noOfUsers; i++)
			{
				temp[i] = new char* [maxfriends];
				for (int j = 0; j < maxfriends; j++)
				{
					temp[i][j] = new char[4];
				}
			}

			users = new User * [noOfUsers];
			char temp2[4];//To read Page ID in the form of character
			Page* tempPageID;//To temporarily store liked page
			User* tempFriendID;//To Store the found ID of Friend Temporarily
			for (int i = 0; i < noOfUsers; i++)
			{
				tempPageID = nullptr;
				tempFriendID = nullptr;
				users[i] = new User;
				users[i]->ReadDataFormFile(fin);

				//Friends
				count[i] = 0;
				while (1)
				{

					fin >> temp[i][count[i]];
					if (temp[i][count[i]][0] == '-')
						break;
					count[i]++;
				}

				//Liked Pages
				for (int j = 0; j < maxPages; j++)
				{
					fin >> temp2;
					if (temp2[0] == '-')
					{
						break;
					}
					tempPageID = SearchPageByID(temp2);
					if (tempPageID)
					{
						users[i]->AddLikedPages(tempPageID);
					}

				}

			}

			//Friends
			for (int i = 0; i < noOfUsers; i++)//This loop is for setting the pointer of friends
			{
				for (int j = 0; j < count[i]; j++)
				{

					tempFriendID = SearchUserByID(temp[i][j]);
					if (tempFriendID)
					{
						users[i]->AddFriends(tempFriendID);
					}
				}
			}

			for (int i = 0; i < noOfUsers; i++)
			{
				for (int j = 0; j < maxfriends; j++)
				{
					delete[] temp[i][j];
				}
				delete[] temp[i];
			}
			delete[] temp;
			temp = nullptr;
			fin.close();
		}
		else
		{
			cout << "\nUnable to open file\n";
		}

	}
	void LoadPagesFromFile(const char* filename)
	{
		ifstream fin(filename);
		if (filename)
		{
			fin >> noOfPages;
			pages = new Page * [noOfPages];
			for (int i = 0; i < noOfPages; i++)
			{
				pages[i] = new Page;
				pages[i]->ReadDataFromFile(fin);
			}
			fin.close();
		}
		else
		{
			cout << "\nUnable to open file\n";
		}
	}
	void LoadPostsFromFile(const char* filename)
	{
		ifstream fin(filename);
		if (fin)
		{
			fin >> noOfPosts;
			char temp[100];

			posts = new Post * [noOfPosts];

			Object* tempsharedBy;//To temporarily store the pointer of user who shared the post
			for (int i = 0; i < noOfPosts; i++)
			{
				tempsharedBy = nullptr;

				posts[i] = new Post;
				posts[i]->ReadDataFromFile(fin);

				fin >> temp;
				tempsharedBy = SearchObjectByID(temp);//To temporarily store the pointer of user who shared
				posts[i]->SetSharedBy(tempsharedBy);
				tempsharedBy->AddPost(posts[i]);

				fin >> temp;
				for (int j = 0; temp[0] != '-'; j++)
				{
					tempsharedBy = nullptr;

					tempsharedBy = SearchObjectByID(temp);
					posts[i]->SetLikedBy(tempsharedBy);
					fin >> temp;
				}
			}
			fin.close();
		}
		else
		{
			cout << "\n\nUnable to open file\n\n";
		}
	}
	void LoadCommentsFromFile(const char* filename)
	{
		ifstream fin(filename);
		if (fin)
		{
			fin >> noOfComments;
			char temp[100];
			char* id = nullptr;
			char* postid = nullptr;
			char* commenter = nullptr;
			char* text = nullptr;

			Object* tempcommentBy = nullptr;//to temporarily store the object who has commented on a post
			comments = new Comment * [noOfComments];
			for (int i = 0; i < noOfComments; i++)
			{
				comments[i] = new Comment;

				fin >> temp;
				id = Helper::GetStringFromBuffer(temp);
				fin >> temp;
				postid = Helper::GetStringFromBuffer(temp);
				Post* ptr = SearchPostByID(postid);
				fin >> temp;
				commenter = Helper::GetStringFromBuffer(temp);

				fin.get(temp[0]);//to avoid space reading from commente text
				fin.getline(temp, 100);
				text = Helper::GetStringFromBuffer(temp);
				tempcommentBy = SearchObjectByID(commenter);
				ptr->AddComment(comments[i]);
				comments[i]->SetValue(id, text, tempcommentBy);

				if (postid)
					delete[] postid;
				postid = nullptr;
				if (commenter)
					delete[] commenter;
				commenter = nullptr;
			}

			fin.close();
		}
		else
		{
			cout << "\n\n--------------------Unable to open Comments file-----------------------\n\n";
		}
	}
	Page* SearchPageByID(const char* word)
	{

		for (int i = 0; i < noOfPages; i++)
		{
			if (Helper::Compare(word, pages[i]->GetID()))
			{
				return pages[i];
			}

		}

		return nullptr;
	}
	User* SearchUserByID(const char* word)
	{
		for (int i = 0; i < noOfUsers; i++)
		{
			if (Helper::Compare(word, users[i]->GetID()))
			{
				return users[i];
			}
		}
		return nullptr;
	}

	Post* SearchPostByID(const char* word)
	{
		for (int i = 0; i < noOfPosts; i++)
		{

			if (Helper::Compare(word, posts[i]->GetID()))
			{
				return posts[i];
			}
		}
		return nullptr;
	}
	Object* SearchObjectByID(const char* word)
	{
	
		if (word[0] == 'u')
		{
			return SearchUserByID(word);
		
		}
		else if (word[0] == 'p')
		{
			return  SearchPageByID(word);
		
		}
		else
		{
			cout << "\n-----------------------------\n\nId is invalid\n\n----------------------------\n";
			return nullptr;
		}
	
	}

	void LoadData()
	{
		LoadPagesFromFile("Pages.txt");
		LoadUsersFromFile("Users.txt");
		LoadPostsFromFile("Posts.txt");
		LoadCommentsFromFile("Comments.txt");
	}
	
	void Run()
	{

		//Setting Date
		cout << "Set current System Date 15 11 2017\n";
		Date::SetCurrentDate(15, 11, 2017);
		cout << "System Date:\t\t15/11/2017\n\n";

		//Setting User
		cout << "Command:\t\tSet current user: \"u7\" \n";
			User* currentUser = SearchUserByID("u7");
			currentUser->Print();
			cout << " successfully set as Current User\n\n";

			//Viewing Friend List
			cout << "Command:\t\tView friend list\n";
			cout << "-------------------------------------------------------------------------------------------------\n";
			currentUser->ViewFriendList();
			cout << "\n-------------------------------------------------------------------------------------------------\n\n";

			//Viewing Liked Pages
			cout << "Command:\tView Liked Pages";
			cout << "\n-------------------------------------------------------------------------------------------------\n\n";
			currentUser->ViewLikedPages();
			cout << "\n-------------------------------------------------------------------------------------------------\n\n";

			//Viewing Home
			cout << endl << endl << endl << endl;
			cout << "Command:\t\tView Home";
			cout << "\n-------------------------------------------------------------------------------------------------\n";
			currentUser->PrintHome();
			cout << "\n-------------------------------------------------------------------------------------------------\n";

			////Viewing TimeLine

			cout << "Command:\t\tView TimeLine";
			cout << "\n-------------------------------------------------------------------------------------------------\n";
			currentUser->ViewTimeLine();
			cout << "\n-------------------------------------------------------------------------------------------------\n";

			//Viewing Liked List
			cout << "Command:\t\tViewLikedList(post5)";
			SearchPostByID("post5")->ViewLikedList();
			cout << "\n-------------------------------------------------------------------------------------------------\n";

			//Like Post
			cout << "Command:\t\tLikePost(post5)";
			SearchPostByID("post5")->SetLikedBy(currentUser);


			//Viewing Liked List
			cout << endl << endl;
			cout << "Command:\t\tViewLikedList(post5)";
			SearchPostByID("post5")->ViewLikedList();
			cout << "\n-------------------------------------------------------------------------------------------------\n";


			//Commenting
			char* com = nullptr;
			Helper::StringCopy(com, "Good Luck for your Result");
			cout << "Command:\t\tPostComment(post4 , " << com << ")";
			Comment* commentPtr = new Comment;
			commentPtr->SetValue(Helper::createID("c", ++noOfComments), com, currentUser);
			SearchPostByID("post4")->AddComment(commentPtr);


			//View Post
			cout << endl << endl;
			cout << "Command:\t\tViewPost(post4)";
			cout << endl;
			SearchPostByID("post4")->Print();
			cout << "\n-------------------------------------------------------------------------------------------------\n";

			//Commenting
			com = nullptr;
			Helper::StringCopy(com, "Thanks for the wishes");
			cout << "Command:\t\tPostComment(post8, " << com << ")";
			commentPtr = new Comment;
			commentPtr->SetValue(Helper::createID("c", ++noOfComments), com, currentUser);
			SearchPostByID("post8")->AddComment(commentPtr);


			//View Post
			cout << endl << endl;
			cout << "Command:\t\tViewPost(post8)";
			cout << endl;
			SearchPostByID("post8")->Print();
			cout << "\n-------------------------------------------------------------------------------------------------\n";

			//Viewing Memories
			cout << "\n-------------------------------------------------------------------------------------------------\n";
			cout << "Command:\t\tSeeYourMemories()";
			currentUser->SeeMemories();

			//Sharing Memories
			cout << "\n-------------------------------------------------------------------------------------------------\n";
			char* caption = nullptr;
			Helper::StringCopy(caption, "Never thought I will be specialist in this field...");
			cout << "Command:\t\tShareMemory" << "(post10, " << caption << ")";
			Post* ptr=SearchPostByID("post10");
			if ((ptr->GetDateOfSharing()).IsEqualToCurrent())
			{
				Memory* memory = new Memory(ptr);
				memory->ShareMemory(Helper::createID("post", ++noOfPosts), currentUser, caption);
				currentUser->AddPost(memory);
			}
			cout << endl;

			//Viewing TimeLine

			cout << "Command:\t\tView TimeLine";
			cout << "\n-------------------------------------------------------------------------------------------------\n";
			currentUser->ViewTimeLine();
			cout << "\n-------------------------------------------------------------------------------------------------\n";


			//Viewing Page
			char tempP[] = "p1";
			cout << "Command:\t\tViewPage(p1)";
			Page* ptrPage = SearchPageByID(tempP);
			ptrPage->PrintPosts();


			//Setting Current User

			cout << "\n\n\nCommand:\t\tSet current user: \"u11\"";
			currentUser = SearchUserByID("u11");
			cout << endl;
			currentUser->Print();
			cout << " successfully set as a current user\n";

			//Viewing Home
			cout << "Command:\tView Home\n";
			currentUser->PrintHome();

			//Viewing Timeline
			cout << "Command:\tView TimeLine\n";
			currentUser->ViewTimeLine();
	}
	~Facebook()
	{
		if (users)
		{
			for (int i = 0; i < noOfUsers; i++)
				delete users[i];
			delete[] users;
		}

		if (pages)
		{
			for (int i = 0; i < noOfPages; i++)
				delete pages[i];
			delete[] pages;
		}
		if (posts)
		{
			delete[] posts;
		}

		if (comments)
		{
			delete[] comments;
		}
	}
};


int main()
{
	Facebook fb;
	fb.LoadData();
	fb.Run();
	return 0;
}
