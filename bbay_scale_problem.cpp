#include <string>
#include <iostream>
#include <utility>
#include <set>
#include <tuple>
#include <unordered_map>
#include <cctype> //for isdigit
#include <algorithm> //swap


template<typename T>
class ScaleBalanceTree
{

	//example answer set[{B1,25,0},{B2,0,13}]
	using BalanceResult = std::set<std::tuple<std::string, int, int>>;

	struct TreeNode
	{
		TreeNode* left;
		TreeNode* right;
		T weight;
		std::string name;
	};

 public:
	ScaleBalanceTree() = default;
	~ScaleBalanceTree()
	{
		for(auto const&[key, node] : nodeMap_)
		{
			delete node;
		}
	}

	ScaleBalanceTree(ScaleBalanceTree const&) = delete;
	ScaleBalanceTree& operator=(ScaleBalanceTree const&) = delete;

	ScaleBalanceTree(ScaleBalanceTree&& rhs)
	{
		root_ = rhs.root_;
		rhs.root_ = nullptr;
		nodeMap_ = std::move(rhs.nodeMap_);
	}

	ScaleBalanceTree& operator=(ScaleBalanceTree rhs)
	{
		swap(this, &rhs);

		return *this;
	}

	std::string findRoot()
	{
		std::unordered_map<std::string, int> inDegree{};

		for(auto const& [key, val] : nodeMap_)
		{
			if(val->weight == -1)
				inDegree[key];

			if(val->left && val->left->weight == -1)
			{
				//std::cout<<"add node = " << val->left->name <<"\n";
				inDegree[val->left->name]++;
			}

			if(val->right && val->right->weight == -1)
			{
				//std::cout<<"add node = " << val->right->name <<"\n";
				inDegree[val->right->name]++;
			}

		}

		std::string root;

		for(auto const& [key, val] : inDegree)
		{
			//std::cout<< key << "==>" << val << "\n";
			if(val == 0)
				root = std::move(key);
		}

		return root;
	}
	TreeNode* addNodes(std::string const& rootStr, std::string const& leftStr, std::string const& rightStr)
	{

		auto [rootRet, rootNum] = checkIfDigit(rootStr);
		auto [lret, lNum] = checkIfDigit(leftStr);
		auto [rret, rNum] = checkIfDigit(rightStr);

		TreeNode* node = nullptr;

		if(nodeMap_.find(rootStr) == nodeMap_.end())
			nodeMap_[rootStr] = node = constructNode(rootStr, rootRet, rootNum);
		else
			node = nodeMap_[rootStr];

		//std::cout<<"adding node " << rootStr << " with value = " << nodeMap_[rootStr]->weight <<"\n";

		if(nodeMap_.find(leftStr) == nodeMap_.end())
			nodeMap_[leftStr] = node->left = constructNode(leftStr, lret, lNum);
		else
			node->left = nodeMap_[leftStr];

		//std::cout<<"adding node " << leftStr << " with value = " << nodeMap_[leftStr]->weight <<"\n";


		if(nodeMap_.find(rightStr) == nodeMap_.end())
			nodeMap_[rightStr] = node->right = constructNode(rightStr, rret, rNum);
		else
			node->right = nodeMap_[rightStr];

		//std::cout<<"adding node " << rightStr << " with value = " << nodeMap_[rightStr]->weight <<"\n";


		auto curRoot  = findRoot();

		root_ = nodeMap_[curRoot];

		return node;
	}

	void printTree()
	{
		printCurTree(root_);
	}


	void printBalanceScale()
	{
		for(auto itr = ans.begin(); itr != ans.end(); ++itr)
		{
			auto const& [name, lw, rw] = *itr;

			std::cout << name << "," << lw << "," << rw <<"\n";
		}
	}

	void balanceScale()
	{
		doBalanceScale(root_);
	}

	BalanceResult getBalanceResult()
	{
		return ans;
	}

private:

	std::pair<bool, int> checkIfDigit(std::string const& nodeStr)
	{

		if((nodeStr[0] >= 'a' && nodeStr[0] <= 'z') || (nodeStr[0] >= 'A' && nodeStr[0] <= 'Z') )
			return {false, -1};

		int num = std::atoi(nodeStr.c_str());

		return {true, num};
	}

	int doBalanceScale(TreeNode* node)
	{
		if(!node)
			return 0;

		if(!node->left && !node->right)
		{
			//its a leaf node and not a balance scale(defensive check)
			if(node->weight != -1)
				return node->weight;
			else
				return 0;
		}
			
		auto leftWeight = doBalanceScale(node->left);
		auto rightWeight = doBalanceScale(node->right);

		if(node->weight == -1)
		{
			//this means its a balance scale
			auto diff = std::abs(leftWeight - rightWeight);

			ans.insert(std::tuple{node->name, (leftWeight < rightWeight ? diff : 0), (rightWeight < leftWeight ? diff : 0) });

			return 1 + leftWeight + rightWeight + diff;
		}
		else
		{
			//its not a scale but another weight, not sure if input can have thisuse case
			//lets still handle it, return total weight without any balace or +1 for scale

			return node->weight + leftWeight + rightWeight;
		}

	}
	void printCurTree(TreeNode* node)
	{
		if(!node)
			return;

		if(node->left)
			printCurTree(node->left);

		std::cout << node->name << "\n";

		if(node->right)
			printCurTree(node->right);
	}

	TreeNode* constructNode(std::string nodeStr, bool isNum, int num)
	{
		auto* node =  new TreeNode{nullptr, nullptr, (isNum ? num : -1), std::move(nodeStr) };
		return node;
	}

	void swap( ScaleBalanceTree* lhs, ScaleBalanceTree* rhs)
	{
		using std::swap;
		swap(lhs, rhs);
	}

	BalanceResult ans;

	TreeNode* root_;
	std::unordered_map<std::string, TreeNode*> nodeMap_;
};



int main()
{
	std::string line;

	ScaleBalanceTree<int> sbTree;

	while(getline(std::cin, line))
	{
		//skip empty lines
		if(line.empty())
			continue;

		//sanitize the input skip all leading spaces if any
		size_t start = line.find_first_not_of(' ');

		if(start != std::string::npos)
			line = line.substr(start);

		//skip '#' as its a comment
		if(line[0] == '#')
			continue;

		size_t pos = 0;
		start = 0;

		pos = line.find(',', pos);

		if(pos == std::string::npos)
		{
			std::cout<<"input not correct!!!!";
			exit(1);
		}

		std::string rootStr = line.substr(start, pos - start);

		start = ++pos;

		pos = line.find(',', pos);

		if(pos == std::string::npos)
		{
			std::cout<<"input not correct!!!!";
			exit(1);
		}

		std::string leftStr = line.substr(start, pos - start);

		start = ++pos;

		std::string rightStr = line.substr(start);

		if(rightStr.empty())
		{
			std::cout<<"input not correct!!!!";
			exit(1);
		}

		std::cout<<rootStr<< " : "<< leftStr <<" : " << rightStr <<"\n";
	
		sbTree.addNodes(rootStr, leftStr, rightStr);

	}

	//sbTree.printTree();
	sbTree.balanceScale();
	sbTree.printBalanceScale();

}