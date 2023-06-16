#include "bm_common.h"
#include "bm_timer.h"

void bmdev_timer_init(struct bm_device_info *bmdi)
{
	nv_timer_reg_write(bmdi, 0x0, 0x0);
}

unsigned long bmdev_timer_get_cycle(struct bm_device_info *bmdi)
{
	unsigned long cur_clock = 0ULL;
	u32 high_counter = nv_timer_reg_read(bmdi, 0x8);
	u32 low_counter = nv_timer_reg_read(bmdi, 0x4);
	u32 new_high_counter = nv_timer_reg_read(bmdi, 0x8);

	while (new_high_counter != high_counter) {
		high_counter = new_high_counter;
		new_high_counter = nv_timer_reg_read(bmdi, 0x8);
		low_counter = nv_timer_reg_read(bmdi, 0x4);
	}
	cur_clock = low_counter | ((u64)high_counter << 32);

	return cur_clock;
}

unsigned long bmdev_timer_get_time_ms(struct bm_device_info *bmdi)
{
	unsigned long clock_num = bmdev_timer_get_cycle(bmdi);

	return (clock_num * BM_TIMER_PERIOD_NS) / 1000000;
}

unsigned long bmdev_timer_get_time_us(struct bm_device_info *bmdi)
{
	unsigned long clock_num = bmdev_timer_get_cycle(bmdi);

	return (clock_num * BM_TIMER_PERIOD_NS) / 1000;
}

int bmdrv_timer_start(struct bm_device_info *bmdi, struct timer_ctx *ctx, int timeout)
{
	ctx->timestamp = bmdev_timer_get_time_ms(bmdi);
	ctx->timeout = timeout;

	return 0;
}

void bmdrv_timer_stop(struct bm_device_info *bmdi, struct timer_ctx *ctx)
{
}

int bmdrv_timer_remain(struct bm_device_info *bmdi, struct timer_ctx *ctx)
{
	uint64_t time_elapse, time_remain;

	time_elapse = bmdev_timer_get_time_ms(bmdi) - ctx->timestamp;

	/* make sure wait at least timeout milliseconds */
	if (time_elapse == ctx->timeout)
		time_remain = 1;
	else if (time_elapse > ctx->timeout)
		time_remain = 0;
	else
		time_remain = ctx->timeout - time_elapse;

	return time_remain;
}
