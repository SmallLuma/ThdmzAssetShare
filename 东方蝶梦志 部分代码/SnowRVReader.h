#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include "BKDRHash.h"

namespace Basic{

	class SnowRVReader final{
    private:
        std::map<uintptr_t,int> m_ints;
        std::map<uintptr_t,double> m_flts;
        std::map<uintptr_t,std::string> m_strs;

        std::string Trim(const std::string& s);

        void loadFromBin(const std::shared_ptr<std::vector<uint8_t> >&);
        void loadFromText(const std::shared_ptr<std::vector<uint8_t> >&);
	public:
	    SnowRVReader(const std::string& path);
        std::string GetStringImpl(uintptr_t hash) const ;
        int GetIntImpl(uintptr_t) const ;
        double GetDoubleImpl(uintptr_t) const ;
        void SaveToBinaryFile(const std::string&) const ;

		inline void SetIntImpl(uintptr_t hash, int i) { m_ints[hash] = i; }
		inline void SetDoubleImpl(uintptr_t hash, double i) { m_flts[hash] = i; }
		inline void SetStringImpl(uintptr_t hash, const std::string& i) { m_strs[hash] = i; }

		class SnowRVCompileFailed :public std::runtime_error {
			using std::runtime_error::runtime_error;
		};
		class ValueNotFound :public std::runtime_error {
			using std::runtime_error::runtime_error;
		};

#define GetInt(x) GetIntImpl(Basic::BKDRHash(x))
#define GetDouble(x) GetDoubleImpl(Basic::BKDRHash(x))
#define GetString(x) GetStringImpl(Basic::BKDRHash(x))

#define SetInt(x) SetIntImpl(Basic::BKDRHash(x))
#define SetDouble(x) SetDoubleImpl(Basic;:BKDRHash(x))
#define SetString(x) SetStringImpl(Basic::BKDRHash(x))
	};


}
