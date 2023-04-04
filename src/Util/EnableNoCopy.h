#pragma once
namespace CUtil {
	class EnAbleNoCopy {
	public:
		EnAbleNoCopy() = default;
		EnAbleNoCopy(const EnAbleNoCopy& rhs) = delete;
		EnAbleNoCopy& operator=(const EnAbleNoCopy& ths) = delete;
		EnAbleNoCopy(EnAbleNoCopy&& rhs) = default;
		EnAbleNoCopy& operator=(EnAbleNoCopy&& rhs) = default;
	};
}