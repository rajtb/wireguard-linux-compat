#include "compat/compat.h"

inline void dst_cache_reset_now(struct dst_cache *dst_cache)
{
	int i;

	if (!dst_cache->cache)
		return;

	dst_cache->reset_ts = jiffies;
	for_each_possible_cpu(i) {
		struct dst_cache_pcpu *idst = per_cpu_ptr(dst_cache->cache, i);
		struct dst_entry *dst = idst->dst;

		idst->cookie = 0;
		idst->dst = NULL;
		dst_release(dst);
	}
}
