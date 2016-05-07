namespace CS2312 {
	/* general template */
	template <typename T>
	class less {
	public:
		bool operator() (const T & a, const T & b) {
			return a < b;
		}
	};

	/* specialization for C-strings */
	template <>
	class less<const char *> {
	public:
		bool operator() (const char *a, const char *b) {
			return std::string(a) < std::string(b);
		}
	};
};

