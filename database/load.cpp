#include <mysqlx/xdevapi.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace mysqlx;

void savePatternsToFile(const string &filename)
{
    ofstream outFile(filename);

    try
    {
        // 设置数据库连接
        Session sess("localhost", 33060, "your_user", "your_password");
        Schema db = sess.getSchema("IDSFeatures");
        Table features = db.getTable("Features");

        // 执行查询
        RowResult res = features.select("FeatureName", "FeaturePattern", "PatternType").execute();

        // 写入文件
        for (Row row : res)
        {
            outFile << row[0].get<string>() << "#" << row[1].get<string>() << "#" << row[2].get<string>() << endl;
        }
        cout << "Patterns have been saved to " << filename << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
        outFile.close();
    }

    outFile.close();
}

int main()
{
    savePatternsToFile("patternfile.txt");
    return 0;
}
